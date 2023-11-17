#include "widgets/tabs/TabWindow/tabwindow.h"
#include "ui_tabwindow.h"

QString TabWindow::newTabIconPath = ":/rec/img/icons/new.png";

TabWindow::TabWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabWindow)
{
    ui->setupUi(this);

    //this->editorTabBar = new EditorTabBar();
    // this->setTabBar(editorTabBar);

    this->createEditorTab();

    // NewTab* newTab = new NewTab();
    //this->setCornerWidget(newTab, Qt::TopLeftCorner);

    connect(ui->newTab, &QAbstractButton::clicked, this, &TabWindow::createEditorTab);
    // connect(this, &TabWindow::tabBarClicked, this, &TabWindow::switchTab);
}

TabWindow::~TabWindow()
{
    delete ui;
}

void TabWindow::createEditorTab() {
    MainEditor* editor = new MainEditor();
    this->createTabFromExisting(editor, "New File");
}

void TabWindow::closeTab() {

}

void TabWindow::createTabFromExisting(QWidget* widget, const QString& tabName) {
    this->setUpdatesEnabled(false);

    ClosableTab* tab = new ClosableTab();
    tabs.insert(std::pair<QUuid, ClosableTab*>(tab->getId(), tab));

    tab->setText(tabName);
    ui->tabs->addWidget(tab);
    this->setUpdatesEnabled(true);


    connect(tab, &ClosableTab::onFocused, this, [this, tab](){ switchTab(tab->getId()); });
    switchTab(tab->getId());
}

void TabWindow::switchTab(QUuid newTabId) {
    if (tabs.size() > 1) tabs[currentTab]->setFocus(false);
    currentTab = newTabId;

    // Switch frame

}
