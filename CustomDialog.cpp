#include "CustomDialog.h"

CustomDialog::CustomDialog(QWidget *parent) :
    QDialog(parent)
{
    QFormLayout *layout = new QFormLayout;

    characterLineEdit = new QLineEdit;
    messageLineEdit = new QLineEdit;
    messagePropertiesLineEdit = new QLineEdit;

    layout->addRow(new QLabel("Character:"), characterLineEdit);
    layout->addRow(new QLabel("Message:"), messageLineEdit);
    layout->addRow(new QLabel("Message Properties:"), messagePropertiesLineEdit);

    QPushButton *button = new QPushButton("Submit");
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &QDialog::accept);

    setLayout(layout);
}

QString CustomDialog::getCharacter() {
    return characterLineEdit->text();
}

QString CustomDialog::getMessage() {
    return messageLineEdit->text();
}

QString CustomDialog::getMessageProperties() {
    return messagePropertiesLineEdit->text();
}
