#include "newtab.h"
#include "ui_newtab.h"

NewTab::NewTab(QToolButton *parent) :
    QToolButton(parent),
    ui(new Ui::NewTab)
{
    ui->setupUi(this);
}

NewTab::~NewTab()
{
    delete ui;
}
