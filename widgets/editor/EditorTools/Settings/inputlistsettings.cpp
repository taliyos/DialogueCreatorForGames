#include "inputlistsettings.h"
#include "ui_inputlistsettings.h"

InputListSettings::InputListSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputListSettings)
{
    ui->setupUi(this);
}

InputListSettings::~InputListSettings()
{
    delete ui;
}
