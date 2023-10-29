#include "fieldconnection.h"
#include "ui_fieldconnection.h"

#include <QCheckBox>

FieldConnection::FieldConnection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FieldConnection)
{
    ui->setupUi(this);
}

FieldConnection::~FieldConnection()
{
    delete ui;
}

QCheckBox* FieldConnection::getAuto() {
    return ui->checkBox;
}

void FieldConnection::setAutoText(std::string text) {
    ui->checkBox->setText(QString::fromStdString(text));
}
