#include "newtab.h"
#include "ui_newtab.h"

NewTab::NewTab(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::NewTab)
{
    ui->setupUi(this);
}

NewTab::~NewTab()
{
    delete ui;
}
