#include "widgets/tabs/TabWindow/tabwindow.h"
#include "ui_tabwindow.h"

QString TabWindow::newTabIconPath = ":/rec/img/icons/new.png";

TabWindow::TabWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TabWindow)
{
    ui->setupUi(this);

    this->createEditorTab();

    connect(ui->newTab, &QAbstractButton::clicked, this, &TabWindow::createEditorTab);

}

TabWindow::~TabWindow()
{
    delete ui;
}

void TabWindow::createEditorTab() {
    MainEditor* editor = new MainEditor();
    this->createTabFromExisting(editor, "New File");
}

void TabWindow::createTabFromExisting(QWidget* widget, const QString& tabName) {
    this->setUpdatesEnabled(false);

    ClosableTab* tab = new ClosableTab();
    tabs.insert(std::pair<QUuid, ClosableTab*>(tab->getId(), tab));
    tabContents.insert(std::pair<QUuid, QWidget*>(tab->getId(), widget));

    tab->setText(tabName);
    ui->tabs->addWidget(tab);
    this->setUpdatesEnabled(true);

    // Connect Focus and Close signals
    connect(tab, &ClosableTab::onFocused, this, [this, tab](){ switchTab(tab->getId()); });
    connect(tab, &ClosableTab::onClose, this, [this, tab](){ closeTab(tab->getId()); });
    switchTab(tab->getId());

    updateTabs();
}

void TabWindow::switchTab(const QUuid newTabId) {
    if (tabs.size() > 1) tabs[currentTab]->setFocus(false);

    // Switch active window
    if (currentWidget) {
        ui->verticalLayout->replaceWidget(currentWidget, tabContents[newTabId]);
        currentWidget->hide();
        tabContents[newTabId]->show();
    }
    else ui->verticalLayout->replaceWidget(ui->window, tabContents[newTabId]);

    currentTab = newTabId;
    currentWidget = tabContents[newTabId];
}

void TabWindow::closeTab(const QUuid tabId) {
    // Don't allow the tab to be closed if there's only one tab
    if (tabs.size() <= 1) return;

    ClosableTab* tab = tabs[tabId];
    QWidget* tabContent = tabContents[tabId];
    tabs.erase(tabId);
    tabContents.erase(tabId);

    if (currentTab == tabId) {
        currentTab = tabs.begin()->first;
        tabs[currentTab]->setFocus(true, false);

        switchTab(currentTab);
    }

    // Cleanup removed tab
    delete tab;
    delete tabContent;

    updateTabs();

}

void TabWindow::updateTabs() {
    std::unordered_map<QUuid, ClosableTab*>::iterator itr = tabs.begin();

    bool closeTabEnabled = true;

    if (tabs.size() <= 1) {
        closeTabEnabled = false;
    }

    for (; itr != tabs.end(); itr++) {
        itr->second->setCloseTabEnabled(closeTabEnabled);
    }
}
