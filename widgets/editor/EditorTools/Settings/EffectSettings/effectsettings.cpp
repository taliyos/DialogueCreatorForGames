#include "effectsettings.h"
#include "ui_effectsettings.h"

EffectSettings::EffectSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EffectSettings)
{
    ui->setupUi(this);

    setWindowTitle("Effect Settings");
}

EffectSettings::~EffectSettings()
{
    delete ui;
}

