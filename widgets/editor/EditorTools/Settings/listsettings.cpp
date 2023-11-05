#include "listsettings.h"
#include <QLineEdit>
#include "ui_listsettings.h"

ListSettings::ListSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListSettings)
{
    ui->setupUi(this);
    data = new list<string>();
    listElements = new list<QLineEdit*>();
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
    QLineEdit* qLine = new QLineEdit("OPTION", ui->listView);
    listElements->push_back(qLine);
    qLine->show();
}
void ListSettings::eraseOption(int index)
{
    list<string>::iterator itr = data->begin();
    list<QLineEdit*>::iterator itr2 = listElements->begin();
    for(int i = 0; i < index; i++)
    {
        itr++;
        itr2++;
    }
    // Delete the UI element
    delete (*itr2);
    // Wipe the element and string from their lists
    listElements->erase(itr2);
    data->erase(itr);
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
    list<QLineEdit*>::iterator itr2 = listElements->begin();
    // fill in the text
    for(int i = 0; i < data->size(); i++)
    {
        (*itr2)->setText(QString::fromStdString(*itr));
        itr++;
        itr2++;
    }
}

void ListSettings::saveOptions()
{
    for(QLineEdit* element : (*listElements))
    {
        data->push_back(element->text().toStdString());
    }
}
