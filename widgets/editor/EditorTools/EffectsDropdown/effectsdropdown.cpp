#include "effectsdropdown.h"
#include "ui_effectsdropdown.h"

EffectsDropdown::EffectsDropdown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EffectsDropdown)
{
    ui->setupUi(this);
}

EffectsDropdown::~EffectsDropdown()
{
    delete ui;
}
