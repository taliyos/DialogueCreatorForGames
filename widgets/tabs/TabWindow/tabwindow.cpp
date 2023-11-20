#include "widgets/tabs/TabWindow/tabwindow.h"
#include "ui_tabwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>

QString TabWindow::newTabIconPath = ":/rec/img/icons/new.png";

TabWindow::TabWindow(QWidget *parent) : QMainWindow(parent),
                                        ui(new Ui::TabWindow)
{
    ui->setupUi(this);

    this->createEditorTab();

    connect(ui->newTab, &QAbstractButton::clicked, this, [this]()
            { createEditorTab(); });
}

TabWindow::~TabWindow()
{
    delete ui;
}

MainEditor* TabWindow::createEditorTab()
{
    return this->createEditorTab("New File");
}

MainEditor* TabWindow::createEditorTab(const QString tabName)
{
    MainEditor* editor = new MainEditor();


    this->createTabFromExisting(editor, tabName);

    return editor;
}

void TabWindow::createTabFromExisting(TabableWidget* widget, const QString &tabName)
{
    this->setUpdatesEnabled(false);

    ClosableTab *tab = new ClosableTab();
    tabs.insert(std::pair<QUuid, ClosableTab*>(tab->getId(), tab));
    tabContents.insert(std::pair<QUuid, TabableWidget*>(tab->getId(), widget));

    tab->setText(tabName);
    ui->tabs->addWidget(tab);
    this->setUpdatesEnabled(true);

    // Connect Focus and Close signals
    connect(tab, &ClosableTab::onFocused, this, [this, tab]()
            { switchTab(tab->getId()); });
    connect(tab, &ClosableTab::onClose, this, [this, tab]()
            { closeTab(tab->getId()); });
    switchTab(tab->getId());

    updateTabs();
}

void TabWindow::switchTab(const QUuid newTabId)
{
    if (tabs.size() > 1 && newTabId != currentTab)
        tabs[currentTab]->setFocus(false);

    // Switch active window
    if (currentWidget)
    {
        ui->verticalLayout->replaceWidget(currentWidget, tabContents[newTabId]);
        currentWidget->hide();
        tabContents[newTabId]->show();
    }
    else
        ui->verticalLayout->replaceWidget(ui->window, tabContents[newTabId]);

    currentTab = newTabId;
    currentWidget = tabContents[newTabId];
}

void TabWindow::closeTab(const QUuid tabId)
{
    // Don't allow the tab to be closed if there's only one tab
    if (tabs.size() <= 1)
        return;

    // Find and remove the current tab & contents from the maps
    ClosableTab *tab = tabs[tabId];
    QWidget *tabContent = tabContents[tabId];
    tabs.erase(tabId);
    tabContents.erase(tabId);

    // If the closed tab was focused, assign a new focused tab
    if (currentTab == tabId)
    {
        currentTab = tabs.begin()->first;
        tabs[currentTab]->setFocus(true, false);

        switchTab(tabs.begin()->first);
    }

    // Cleanup removed tab
    delete tab;
    delete tabContent;

    updateTabs();
}

void TabWindow::updateTabs()
{
    std::unordered_map<QUuid, ClosableTab *>::iterator itr = tabs.begin();

    bool closeTabEnabled = true;

    if (tabs.size() <= 1)
    {
        closeTabEnabled = false;
    }

    for (; itr != tabs.end(); itr++)
    {
        itr->second->setCloseTabEnabled(closeTabEnabled);
    }
}

// Actions

void TabWindow::on_actionOpen_triggered()
{
    MainEditor* widget = this->createEditorTab();
    bool result = widget->importJSON();

    if (result) {
        tabs[currentTab]->setText(widget->getFileName());
    }
    else {
        closeTab(currentTab);
    }
}

void TabWindow::on_action_docx_triggered()
{
    bool result = tabContents[currentTab]->importDocx();
    if (result) tabs[currentTab]->setText(tabContents[currentTab]->getFileName());
}


void TabWindow::on_action_txt_triggered()
{
    bool result = tabContents[currentTab]->importText();
    if (result) tabs[currentTab]->setText(tabContents[currentTab]->getFileName());
}

void TabWindow::on_actionSave_triggered()
{
    bool result = tabContents[currentTab]->save();
    if (!result) return;

    // Update the tab's name
    tabs[currentTab]->setText(tabContents[currentTab]->getFileName());

}
void TabWindow::on_actionSaveAs_triggered()
{
    bool result = tabContents[currentTab]->saveAs();
    if (!result) return;

    // Update the tab's name
    tabs[currentTab]->setText(tabContents[currentTab]->getFileName());
}
void TabWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void TabWindow::on_actionNew_triggered()
{
    createEditorTab();
}

void TabWindow::on_actionImport_Preset_triggered()
{
    tabContents[currentTab]->importPreset();
}


void TabWindow::on_actionExport_Preset_1_triggered()
{
    tabContents[currentTab]->exportPreset(1);
}
void TabWindow::on_actionExport_Preset_2_triggered()
{
    tabContents[currentTab]->exportPreset(2);
}
void TabWindow::on_actionExport_Preset_3_triggered()
{
    tabContents[currentTab]->exportPreset(3);
}
void TabWindow::on_actionExport_Preset_4_triggered()
{
    tabContents[currentTab]->exportPreset(4);
}


