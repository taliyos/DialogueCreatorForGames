#include "inputlistfield.h"
#include "ui_inputlistfield.h"

InputListField::InputListField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputListField)
{
    ui->setupUi(this);
}

InputListField::~InputListField()
{
    delete ui;
}
