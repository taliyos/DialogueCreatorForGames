#include "tabs.h"
#include "ui_tabs.h"

Tabs::Tabs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tabs)
{
    ui->setupUi(this);
}

Tabs::~Tabs()
{
    delete ui;
}
