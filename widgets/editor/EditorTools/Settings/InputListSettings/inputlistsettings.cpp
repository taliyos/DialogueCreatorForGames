#include "inputlistsettings.h"
#include "ui_inputlistsettings.h"

InputListSettings::InputListSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputListSettings)
{
    ui->setupUi(this);

    setWindowTitle("Input List Settings");

    data = new list<list<string>>();
    configList = new list<InputListSettingsConfig*>();
    connect(ui->Add, &QAbstractButton::clicked, this, &InputListSettings::addConfig);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &InputListSettings::saveConfigs);
}

InputListSettings::~InputListSettings()
{
    delete ui;
    delete data;
}

/**
 * Adds a config for a list input field.
 */
void InputListSettings::addConfig()
{
    InputListSettingsConfig* config = new InputListSettingsConfig(nullptr, configList->size());
    ui->scrollAreaWidgetContents->layout()->addWidget(config);
    config->show();
    configList->push_back(config);
    // connect erased signal to erase config
    connect(config, &InputListSettingsConfig::erased, this, &InputListSettings::eraseConfig);
}

/**
 * Erases a config from the list of available configs.
 * @param index: the index of the config to erase.
 */
void InputListSettings::eraseConfig(int index)
{
    qDebug() << "Index: " << index;

    list<InputListSettingsConfig*>::iterator itr = configList->begin();
    for(int i = 0; i < index; i++)
    {
        ++itr;
    }
    // Delete the UI element
    (*itr)->deleteLater();
    // Wipe the element and string from their lists
    configList->erase(itr);
    int count = 0;
    for(InputListSettingsConfig* option : (*configList))
    {
        option->setIndex(count);
        count++;
    }
}

/**
 * Loads the config text saved in the data into the UI.
 */
void InputListSettings::loadConfigs()
{
    // remove the configs
    for (InputListSettingsConfig* option : *(configList))
    {
        option->deleteLater();
    }
    configList->clear();
    // re-add the configs
    for (int i = 0; i <  data->size(); i++)
    {
        addConfig();
    }
    // fill in the options of each list config
    list<list<string>>::iterator dataItr = data->begin();
    list<InputListSettingsConfig*>::iterator uiItr = configList->begin();
    for(int i = 0; i < data->size(); i++)
    {
        (*uiItr)->setOptionText((*dataItr));
        uiItr++;
        dataItr++;
    }
}
/**
 * Saves the text options in each config into the data, sends out updates.
 */
void InputListSettings::saveConfigs()
{
    qDebug() << "InputListSettings: Saving Configs";

    data->clear();

    int count = 0;
    list<string> options = {};
    for(InputListSettingsConfig* config : (*configList))
    {
        options = config->getOptionText();
        data->push_back(options);
        sendUpdateField(count);
        count++;
    }

    qDebug() << "InputListSettings: Saved Confgis with " << (*data);
}
/**
 * Sends a signal to update all InputListFields with the given index, using the given options.
 * @param index: the index of the field to update
 * @param options: the options to update the fields with
 */
void InputListSettings::sendUpdateField(int index)
{
    // get the indices
    list<int> indices = {};
    for (int i = 0; i < configList->size(); i++)
    {
        indices.push_back(i);
    }

    // Too large an index
    if (index >= data->size())
    {
        indices.push_back(index);
        emit updateField(index, indices, {});
        return;
    }

    // get the options
    list<list<string>>::iterator itr = data->begin();
    std::advance(itr, index);
    list<string> options = (*itr);
    emit updateField(index, indices, options);
}
