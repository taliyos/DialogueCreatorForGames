#include "settingsoption.h"
#include "ui_settingsoption.h"

SettingsOption::SettingsOption(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::SettingsOption)
{
    qDebug() << "Settings Option: Calling constructor";
    ui->setupUi(this);
    this->index = index;
    connect(getButton(), &QPushButton::clicked, this, &SettingsOption::erase);
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
    emit erased(index);
}

QPushButton* SettingsOption:: getButton(){
    return ui->pushButton;
}

 QLineEdit* SettingsOption::getLineEdit()
{
    return ui->lineEdit;
}
