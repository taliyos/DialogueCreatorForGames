#include "listsettings.h"
#include <QLineEdit>
#include "ui_listsettings.h"
#include <QDialogButtonBox>
#include <data/Fields/MainFields/list/listdata.h>
#include <widgets/editor/MainEditor/maineditor.h>

ListSettings::ListSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListSettings)
{
    ui->setupUi(this);
    data = new std::list<std::string>();
    listElements = new std::list<SettingsOption*>();

    connect(ui->Add, &QAbstractButton::clicked, this, &ListSettings::addOption);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ListSettings::saveOptions);
    connect(this, &ListSettings::optionErased, this, &ListSettings::eraseOption);
}

ListSettings::~ListSettings()
{
    delete data;
    delete listElements;
    delete ui;
}

void ListSettings::addOption()
{
    SettingsOption* option = new SettingsOption(nullptr, listElements->size(), this);
    ui->layout->addWidget(option);
    option->show();
    listElements->push_back(option);
    connect(option->getButton(), &QPushButton::clicked, option, &SettingsOption::erase);
}

void ListSettings::eraseOption(int index)
{
    qDebug() << "Index: " << index;

    std::list<SettingsOption*>::iterator itr = listElements->begin();
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
    // Remove the options
    for (SettingsOption* option : *(listElements))
    {
        option->deleteLater();
    }
    listElements->clear();

    // Re-add the options
    for (int i = 0; i <  data->size(); i++)
    {
        addOption();
    }
    std::list<string>::iterator itr = data->begin();
    std::list<SettingsOption*>::iterator itr2 = listElements->begin();

    // Fill in the text
    for(int i = 0; i < data->size(); i++)
    {
        (*itr2)->getLineEdit()->setText(QString::fromStdString(*itr));
        itr2++;
        itr++;
    }
}

void ListSettings::saveOptions()
{
    qDebug() << "ListSettings: Saving Options";
    data->clear();
    for(SettingsOption* element : (*listElements))
    {
        data->push_back(element->getLineEdit()->text().toStdString());
    }

    // Pack the options
    std::string txt = "";
    for(std::string s : *(data))
    {
        txt += baseDelimiter + s;
    }

    // Send the options off
    emit optionsSaved(txt);
}
