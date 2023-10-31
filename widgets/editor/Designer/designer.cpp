#include "designer.h"
#include "ui_designer.h"

#include "../Fields/TextField/textfield.h"
#include "../FieldConnection/fieldConnection.h"

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

FieldConnection* Designer::createFieldConnection() {
    FieldConnection* fieldConnection = new FieldConnection();

    ui->fieldContainer->addWidget(fieldConnection, 0, Qt::AlignCenter);
    return fieldConnection;
}

TextField* Designer::createTextField() {
    TextField* textField = new TextField();

    ui->fieldContainer->addWidget(textField);
    return textField;
}

QPushButton* Designer::getCreateField() {
    return ui->createField;
}

QWebEngineView* Designer::getPreview() {
    return ui->preview;
}
