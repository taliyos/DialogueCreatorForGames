#include "listsettings.h"
#include <QLineEdit>
#include "ui_listsettings.h"
#include <QDialogButtonBox>

ListSettings::ListSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListSettings)
{
    ui->setupUi(this);
    data = new list<string>();
    listElements = new list<SettingsOption*>();
    connect(ui->Add, &QAbstractButton::clicked, this, &ListSettings::addOption);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ListSettings::saveOptions);
    connect(this, &ListSettings::optionErased, this, &ListSettings::eraseOption);
}

ListSettings::~ListSettings()
{
    delete ui;
    delete[] data;
    // don't delete listElements because they are parented to EditorTools
    //delete[] listElements;
}

void ListSettings::addOption()
{
    SettingsOption* option = new SettingsOption(nullptr, listElements->size(), this);
    ui->verticalLayoutWidget->layout()->addWidget(option);
    option->show();
    listElements->push_back(option);
    connect(option->getButton(), &QPushButton::clicked, option, &SettingsOption::erase);
}

void ListSettings::eraseOption(int index)
{
    qDebug() << "Index: " << index;

    list<SettingsOption*>::iterator itr = listElements->begin();
    for(int i = 0; i < index; i++)
    {
        ++itr;
    }
    // Delete the UI element
    (*itr)->deleteLater();
    // Wipe the element and string from their lists
    listElements->erase(itr);
    int count = 0;
    for(SettingsOption* option : (*listElements))
    {
        option->setIndex(count);
        count++;
    }
}

void ListSettings::loadOptions()
{
    // add missing ui elements if there are any
    int difference = data->size()-listElements->size();
    if (difference > 0)
    {
        for (int i = 0; i < difference; i++)
        {
            addOption();
        }
    }
    list<string>::iterator itr = data->begin();
    list<SettingsOption*>::iterator itr2 = listElements->begin();
    // fill in the text
    for(int i = 0; i < data->size(); i++)
    {
        (*itr2)->getLineEdit()->setText(QString::fromStdString(*itr));
        itr++;
        itr2++;
    }
}

void ListSettings::saveOptions()
{
    data->clear();
    for(SettingsOption* element : (*listElements))
    {
        data->push_back(element->getLineEdit()->text().toStdString());
    }
}
