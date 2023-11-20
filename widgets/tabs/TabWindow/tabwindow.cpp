#include "widgets/tabs/TabWindow/tabwindow.h"
#include "ui_tabwindow.h"

#include "widgets/editor/EditorWindow/editorwindow.h"

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
   EditorWindow* editor = new EditorWindow();
    this->createTabFromExisting(editor, "New File");
}

void TabWindow::createTabFromExisting(QWidget* widget, const QString& tabName) {
    this->setUpdatesEnabled(false);

    ClosableTab* tab = new ClosableTab();
    tabs.insert(std::pair<QUuid, ClosableTab*>(tab->getId(), tab));
    tabContents.insert(std::pair<QUuid, QWidget*>(tab->getId(), widget));

    for (std::unordered_map<QUuid, QWidget*>::iterator itr = tabContents.begin(); itr != tabContents.end(); itr++) {
        QString id = itr->first.toString();
        qInfo(id.toStdString().c_str());
    }

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

    qInfo("Switching tab!");
    QString curr = currentTab.toString();
    QString next = newTabId.toString();
    qInfo() << curr << " -> " << next;

    // Switch active window
    if (currentWidget) {
        qInfo("replacing current widget");
        ui->verticalLayout->replaceWidget(currentWidget, tabContents[newTabId]);
        currentWidget->hide();
        tabContents[newTabId]->show();
    }
    else ui->verticalLayout->replaceWidget(ui->window, tabContents[newTabId]);//layout()->replaceWidget(ui->window, tabContents[newTabId]);

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
