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
     * @brief addConfig
     */
    void addConfig();
    /**
     * @brief eraseConfig
     * @param index
     */
    void eraseConfig(int index);
    /**
     * @brief loadConfigs
     */
    void loadConfigs();
    /**
     * @brief saveConfigs
     */
    void saveConfigs();

    // send an update to a field
    void sendUpdateField(int index);

signals:
    //
    void configErased (int index);
    // signal emitted to update a field
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
