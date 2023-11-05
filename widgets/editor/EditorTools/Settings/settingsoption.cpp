#include "settingsoption.h"
#include "ui_settingsoption.h"

SettingsOption::SettingsOption(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::SettingsOption)
{
    ui->setupUi(this);
    this->index = index;
}

SettingsOption::~SettingsOption()
{
    delete ui;
}
QPushButton* SettingsOption:: getButton(){
    return ui->pushButton;
}




 QLineEdit* SettingsOption::getLineEdit()
{
    return ui->lineEdit;
}
