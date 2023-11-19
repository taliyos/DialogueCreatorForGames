#include "fieldsettings.h"
#include "ui_fieldsettings.h"

FieldSettings::FieldSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FieldSettings)
{
    ui->setupUi(this);
    // set up the settings pages
    listSettingsPage = new ListSettings(this);
    inputListSettingsPage = new InputListSettings(this);
    // connect the buttons to show the settings pages
    connect(getInputListSettingsButton(), &QAbstractButton::clicked, this, &FieldSettings::openInputListSettings);
    connect(getListSettingsButton(), &QAbstractButton::clicked, this, &FieldSettings::openListSettings);
}

FieldSettings::~FieldSettings()
{
    delete ui;
    delete listSettingsPage;
    delete inputListSettingsPage;
}

ListSettings* FieldSettings::getListSettingsPage() { return listSettingsPage; }
InputListSettings* FieldSettings::getInputListSettingsPage() { return inputListSettingsPage; }
QPushButton* FieldSettings::getInputListSettingsButton() { return ui->OpenInputListSettings; }
QPushButton* FieldSettings::getListSettingsButton() { return ui->OpenListSettings; }

void FieldSettings::openListSettings()
{
    listSettingsPage->open();
    listSettingsPage->loadOptions();
}

void FieldSettings::openInputListSettings()
{
    inputListSettingsPage->open();
    inputListSettingsPage->loadConfigs();
}
