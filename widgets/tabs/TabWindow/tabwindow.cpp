#include "widgets/tabs/TabWindow/tabwindow.h"
#include "ui_tabwindow.h"

QString TabWindow::newTabIconPath = ":/rec/img/icons/new.png";

TabWindow::TabWindow(QWidget *parent) :
    QWidget(parent),
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

    tab->setText(tabName);
    ui->tabs->addWidget(tab);
    this->setUpdatesEnabled(true);


    connect(tab, &ClosableTab::onFocused, this, [this, tab](){ switchTab(tab->getId()); });
    connect(tab, &ClosableTab::onClose, this, [this, tab](){ closeTab(tab->getId()); });
    switchTab(tab->getId());

    updateTabs();
}

void TabWindow::switchTab(const QUuid newTabId) {
    if (tabs.size() > 1) tabs[currentTab]->setFocus(false);
    currentTab = newTabId;

    // Switch frame

}

void TabWindow::closeTab(const QUuid tabId) {
    // Don't allow the tab to be closed if there's only one tab
    if (tabs.size() <= 1) return;

    ClosableTab* tab = tabs[tabId];
    tabs.erase(tabId);

    delete tab;

    if (currentTab == tabId) {
        currentTab = tabs.begin()->first;
        tabs[currentTab]->setFocus(true, false);
    }

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
