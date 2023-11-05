#include "settingsoption.h"
#include "ui_settingsoption.h"

SettingsOption::SettingsOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsOption)
{
    ui->setupUi(this);
}

SettingsOption::~SettingsOption()
{
    delete ui;
}

 QLineEdit* SettingsOption::getLineEdit()
{
    return ui->lineEdit;
}
