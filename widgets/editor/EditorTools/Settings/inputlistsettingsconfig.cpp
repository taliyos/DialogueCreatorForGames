#include "inputlistsettingsconfig.h"
#include "ui_inputlistsettingsconfig.h"

InputListSettingsConfig::InputListSettingsConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputListSettingsConfig)
{
    ui->setupUi(this);
}

InputListSettingsConfig::~InputListSettingsConfig()
{
    delete ui;
}
