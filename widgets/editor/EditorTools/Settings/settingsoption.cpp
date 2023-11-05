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

void SettingsOption::erase()
{
    if (listParent != nullptr)
        emit listParent->optionErased(index);
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
