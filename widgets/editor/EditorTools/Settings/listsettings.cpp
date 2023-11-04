#include "listsettings.h"

#include "ui_listsettings.h"

ListSettings::ListSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListSettings)
{
    ui->setupUi(this);
}

ListSettings::~ListSettings()
{
    delete ui;
}
