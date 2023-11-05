#include "settingsoption.h"
#include "ui_settingsoption.h"

#include "widgets/editor/EditorTools/Settings/listsettings.h"

SettingsOption::SettingsOption(QWidget *parent, int index, ListSettings* listParent) :
    QWidget(parent),
    ui(new Ui::SettingsOption)
{
    ui->setupUi(this);
    this->index = index;
    this->listParent = listParent;
}

SettingsOption::~SettingsOption()
{
    delete ui;
}


int SettingsOption::getIndex()
{
    return index;
}

void SettingsOption::setIndex(int value)
{
    index = value;
}

void SettingsOption::erase()
{
    if (listParent != nullptr)
        emit listParent->optionErased(index);
}

QPushButton* SettingsOption:: getButton(){
    return ui->pushButton;
}

 QLineEdit* SettingsOption::getLineEdit()
{
    return ui->lineEdit;
}
