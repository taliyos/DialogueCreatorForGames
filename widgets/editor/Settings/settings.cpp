// settings.cpp
#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

bool Settings::showSettings()
{
    if(isHidden()){
        show();
        return true;
    }
    return false;
}

bool  Settings::hideSettings()
{
    if(! isHidden()){
        hide();
        return true;
    }
    return false;
}


Settings::~Settings()
{
    delete ui;
}

QLineEdit* Settings::getLineEdit() {
    return ui->lineEdit;
}

QCheckBox* Settings::getCheckBox() {
    return ui->checkBox;
}
