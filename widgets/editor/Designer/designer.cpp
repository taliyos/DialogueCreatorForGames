#include "designer.h"
#include "ui_designer.h"

Designer::Designer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Designer)
{
    ui->setupUi(this);
}

Designer::~Designer()
{
    delete ui;
}
