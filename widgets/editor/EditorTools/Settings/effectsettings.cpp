#include "effectsettings.h"
#include "ui_effectsettings.h"

EffectSettings::EffectSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EffectSettings)
{
    ui->setupUi(this);
}

EffectSettings::~EffectSettings()
{
    delete ui;
}

