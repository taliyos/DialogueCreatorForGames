#include "customfieldsettings.h"
#include "ui_customfieldsettings.h"

CustomFieldSettings::CustomFieldSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomFieldSettings)
{
    ui->setupUi(this);
}

CustomFieldSettings::~CustomFieldSettings()
{
    delete ui;
}
