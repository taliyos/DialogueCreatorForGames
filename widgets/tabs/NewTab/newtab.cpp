#include "newtab.h"
#include "ui_newtab.h"

NewTab::NewTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewTab)
{
    ui->setupUi(this);
}

NewTab::~NewTab()
{
    delete ui;
}
