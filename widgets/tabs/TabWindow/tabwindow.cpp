#include "widgets/tabs/TabWindow/tabwindow.h"
#include "ui_tabwindow.h"

QString TabWindow::newTabIconPath = ":/rec/img/icons/new.png";

TabWindow::TabWindow(QTabWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWindow)
{
    ui->setupUi(this);

    this->setMovable(true);

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
    this->insertTab(index, widget, tabName);
}

void TabWindow::switchTab(int index) {
    if (index == this->count() - 1) {
        createEditorTab();
        this->setCurrentIndex(this->count() - 2);
    }
}
