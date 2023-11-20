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

const MainEditor *TabWindow::createEditorTab()
{
    return this->createEditorTab("New File");
}

const MainEditor *TabWindow::createEditorTab(const QString tabName)
{
    MainEditor *editor = new MainEditor();
    this->createTabFromExisting(editor, tabName);

    return editor;
}

void TabWindow::createTabFromExisting(QWidget *widget, const QString &tabName)
{
    this->setUpdatesEnabled(false);

    ClosableTab *tab = new ClosableTab();
    tabs.insert(std::pair<QUuid, ClosableTab *>(tab->getId(), tab));
    tabContents.insert(std::pair<QUuid, QWidget *>(tab->getId(), widget));

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
    if (tabs.size() > 1)
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

        switchTab(currentTab);
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
    // Open the file dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Dialogue File"), "", tr("Dialogue Data (*.json *.docx *.txt)"));
    if (fileName.isEmpty())
        return;

    // Read the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    QFileInfo fileInfo(file.fileName());

    this->createEditorTab(fileInfo.fileName());
    // this->loadFile(fileName);

    file.close();
}
void TabWindow::on_actionSave_triggered()
{
}
void TabWindow::on_actionSaveAs_triggered()
{
}
void TabWindow::on_actionExit_triggered()
{
}

void TabWindow::on_actionCopy_triggered()
{
}
void TabWindow::on_actionPaste_triggered()
{
}
void TabWindow::on_actionCut_triggered()
{
}

void TabWindow::on_actionUndo_triggered()
{
}
void TabWindow::on_actionRedo_triggered()
{
}

void TabWindow::on_actionNew_triggered()
{
}
