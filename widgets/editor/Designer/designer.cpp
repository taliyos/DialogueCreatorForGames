#include "designer.h"
#include "ui_designer.h"

#include "../Fields/TextField/textfield.h"

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

TextField* Designer::createTextField() {
    TextField* textField = new TextField();

    ui->fieldContainer->addWidget(textField);
    return textField;
}

QPushButton* Designer::getCreateField() {
    return ui->createField;
}
