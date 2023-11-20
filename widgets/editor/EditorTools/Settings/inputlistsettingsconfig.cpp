#include "inputlistsettingsconfig.h"
#include "ui_inputlistsettingsconfig.h"

InputListSettingsConfig::InputListSettingsConfig(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::InputListSettingsConfig)
{
    ui->setupUi(this);
    setIndex(index);

    setWindowTitle("Input List Settings");

    this->listElements = new list<SettingsOption*>();
    // on click, call erase
    connect(ui->remove, &QPushButton::clicked, this, &InputListSettingsConfig::erase);
    // on click, call addOption
    connect(ui->add, &QPushButton::clicked, this, &InputListSettingsConfig::addOption);
    // set the widget
}

InputListSettingsConfig::~InputListSettingsConfig()
{
    delete ui;
}

QPushButton* InputListSettingsConfig:: getButton(){
    return ui->remove;
}

QVBoxLayout* InputListSettingsConfig::getScrollLayout()
{
    return ui->scrollLayout;
}

int InputListSettingsConfig::getIndex()
{
    return index;
}

void InputListSettingsConfig::setIndex(int value)
{
    index = value;
    ui->label->setText(QString::fromStdString(std::to_string(index)));
}

void InputListSettingsConfig::addOption()
{
    qDebug() << "InputListSettingsConfig : Adding an option";
    SettingsOption* option = new SettingsOption(nullptr, listElements->size());
    qDebug() << "InputListSettingsConfig : Constructed an option";
    getScrollLayout()->addWidget(option);
    option->show();
    listElements->push_back(option);
    // connect erased signal to erase option
    connect(option, &SettingsOption::erased, this, &InputListSettingsConfig::eraseOption);
}

void InputListSettingsConfig::eraseOption(int index)
{
    qDebug() << "Config Erasing Index : " << index;

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


void InputListSettingsConfig::setOptionText(list<string> options)
{
    // remove the options
    for (SettingsOption* option : *(listElements))
    {
        option->deleteLater();
    }
    listElements->clear();
    // re-add the options
    for (int i = 0; i <  options.size(); i++)
    {
        addOption();
    }
    list<string>::iterator itr = options.begin();
    list<SettingsOption*>::iterator itr2 = listElements->begin();
    // fill in the text
    for(int i = 0; i < options.size(); i++)
    {
        (*itr2)->getLineEdit()->setText(QString::fromStdString(*itr));
        itr2++;
        itr++;
    }
}

const list<string> InputListSettingsConfig::getOptionText()
{
    qDebug() << "InputListSettingsConfig: count was: " << ui->scrollLayout->count();
    list<string> toReturn = list<string>();
    list<SettingsOption*>::const_iterator itr;
    for(itr = listElements->cbegin(); itr != listElements->cend(); itr++)
    {
        toReturn.push_back((*itr)->getLineEdit()->text().toStdString());
    }
    return toReturn;
}

void InputListSettingsConfig::erase()
{
    emit erased(index);
}
