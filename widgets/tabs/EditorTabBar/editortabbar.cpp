#include "editortabbar.h"
#include "ui_editortabbar.h"

EditorTabBar::EditorTabBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorTabBar)
{
    ui->setupUi(this);
}

EditorTabBar::~EditorTabBar()
{
    delete ui;
}

QTabBar* EditorTabBar::getTabBar() {
    return ui->tabBar;
}
