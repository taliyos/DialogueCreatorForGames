#include "fieldconnection.h"
#include "ui_fieldconnection.h"

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
