#include "textfield.h"
#include "ui_textfield.h"

#include <QPushButton>

TextField::TextField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextField)
{
    ui->setupUi(this);

    connect(ui->remove, &QAbstractButton::clicked, this, &TextField::sendRemove);
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

TextData* TextField::getData() {
    return data;
}

void TextField::setData(TextData* data) {
    this->data = data;
}

void TextField::sendRemove() {
    emit removeField(this);
}
