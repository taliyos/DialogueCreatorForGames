#include "presetsettings.h"
#include "ui_presetsettings.h"

PresetSettings::PresetSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetSettings)
{
    ui->setupUi(this);

    setWindowTitle("Preset Settings");
}

PresetSettings::~PresetSettings()
{
    delete ui;
}

