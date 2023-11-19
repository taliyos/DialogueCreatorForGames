#ifndef INPUTLISTSETTINGS_H
#define INPUTLISTSETTINGS_H

#include "data/Fields/fielddata.h"
#include "inputlistsettingsconfig.h"
#include "data/ConnectionData/connectiondata.h"
#include <QDialog>

using namespace std;

namespace Ui {
class InputListSettings;
}

/**
 * @brief The InputListSettings class
 */
class InputListSettings : public QDialog
{
    Q_OBJECT

public:
    explicit InputListSettings(QWidget *parent = nullptr);
    ~InputListSettings();

    // Buttons
    QPushButton* getOK();
    QPushButton* getCancel();

    // List methods
    /**
     * Adds a new config to the UI.
     */
    void addConfig();
    /**
     * Erases the config in thhe UI with the given index.
     * @param index: the index to erase at.
     */
    void eraseConfig(int index);
    /**
     * Loads configs from data into the UI.
     */
    void loadConfigs();
    /**
     * Saves configs from the UI into the data.
     */
    void saveConfigs();

    // send an update to a field
    /**
     * Sends an update signal out for the given index.
     * @param index: the config index to send the update signal for.
     */
    void sendUpdateField(int index);

signals:
    /**
     * A signal emitted that config with given index is erased.
     * @param index: the index of the erased config.
     */
    void configErased (int index);
    // signal emitted to update a field
    /**
     * A signal that informs configs of the given index to update with the given indices and options.
     * @param index: the index we are trying to update.
     * @param indices: the indices we want to update with
     * @param options: the list of options we want to update with.
     */
    void updateField(int index, list<int> indices, list<string> options);

private:
    // the ui
    Ui::InputListSettings *ui;
    // a list of the option lists for each config
    list<list<string>> *data;
    // the list of configurations
    list<InputListSettingsConfig*> *configList;
};

#endif // INPUTLISTSETTINGS_H
