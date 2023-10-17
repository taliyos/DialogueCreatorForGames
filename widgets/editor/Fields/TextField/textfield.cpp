#include "textfield.h"
#include "ui_textfield.h"

TextField::TextField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextField)
{
    ui->setupUi(this);
}

TextField::~TextField()
{
    delete ui;
}

QLineEdit* TextField::getTextField() {
    return ui->textField;
}

QPushButton* TextField::getPreview() {
    return ui->preview;
}
