#include "inputopenfield.h"
#include "ui_inputopenfield.h"

InputOpenField::InputOpenField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputOpenField)
{
    ui->setupUi(this);
}

InputOpenField::~InputOpenField()
{
    delete ui;
}
