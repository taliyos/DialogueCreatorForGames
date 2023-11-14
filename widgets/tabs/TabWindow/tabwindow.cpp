#include "widgets/tabs/TabWindow/tabwindow.h"
#include "ui_tabwindow.h"

#include "widgets/tabs/NewTab/newTab.h"

QString TabWindow::newTabIconPath = ":/rec/img/icons/new.png";

TabWindow::TabWindow(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWindow)
{
    ui->setupUi(this);

    this->editorTabBar = new EditorTabBar();
    this->setTabBar(editorTabBar);

    this->createEditorTab();
    this->addNewTabButton();

    connect(this, &TabWindow::tabBarClicked, this, &TabWindow::switchTab);
}

TabWindow::~TabWindow()
{
    delete ui;
}

void TabWindow::addNewTabButton() {
    QWidget* widget = new QWidget();
    QIcon newTabIcon(TabWindow::newTabIconPath);
    this->addTab(widget, newTabIcon, "");

}

void TabWindow::createEditorTab() {
    MainEditor* editor = new MainEditor();
    this->createTabFromExisting(editor, "New File");
}

void TabWindow::closeTab() {

}

void TabWindow::createTabFromExisting(QWidget* widget, const QString& tabName) {
    int index = this->count() - 2;
    if (index < 0) index = 0;

    this->setUpdatesEnabled(false);
    this->insertTab(index, widget, tabName);
    this->setUpdatesEnabled(true);
}

void TabWindow::switchTab(int index) {
    if (index == this->count() - 1) {
        createEditorTab();
        this->setCurrentIndex(this->count() - 2);
    }
}
