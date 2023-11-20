#include "designer.h"
#include "ui_designer.h"

#include "../Fields/TextField/textfield.h"
#include "../FieldConnection/fieldConnection.h"
#include "../Fields/ListField/listfield.h"

Designer::Designer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Designer)
{
    ui->setupUi(this);

    ui->preview->page()->setBackgroundColor(Qt::transparent);
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

ListField* Designer::createListField() {
    ListField* listField = new ListField();

    ui->fieldContainer->addWidget(listField);
    return listField;
}

void Designer::removeWidget(QWidget* widget) {
    layout()->removeWidget(widget);
}

QPushButton* Designer::getCreateField() {
    return ui->createField;
}

QPushButton* Designer::getExport() {
    return ui->quickExport;
}

QWebEngineView* Designer::getPreview() {
    return ui->preview;
}
