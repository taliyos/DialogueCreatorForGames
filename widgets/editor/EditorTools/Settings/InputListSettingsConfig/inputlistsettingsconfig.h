#ifndef INPUTLISTSETTINGSCONFIG_H
#define INPUTLISTSETTINGSCONFIG_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "widgets/editor/EditorTools/Settings/SettingsOption/settingsoption.h"

using namespace std;

class InputListSettings;

namespace Ui {
class InputListSettingsConfig;
}
/**
 * A widget that holds a list of SettingsOptions UI elements.
 * Essentially acts as an editable list.
 */
class InputListSettingsConfig : public QWidget
{
    Q_OBJECT

public:
    explicit InputListSettingsConfig(QWidget *parent = nullptr, int index = 0);
    ~InputListSettingsConfig();

    QVBoxLayout* getScrollLayout();
    QPushButton* getButton();
    int getIndex();
    void setIndex(int value);
    /**
     * Add an option to the UI and list of options.
     */
    void addOption();
    /**
     * Erase the option at the given index.
     * @param index: the index to delete at.
     */
    void eraseOption(int index);
    /**
     * Sets the options for the config.
     * @param options: the options to be set to.
     */
    void setOptionText(list<string> options);
    /**
     * Gets a list of strings by taking the text from the ui.
     * @return a list of options taken from the ui.
     */
    const list<string> getOptionText();
    /**
     * Sends out the erased signal with this config's index.
     */
    void erase();

signals:
    /**
     * A signal sent out informing others that this config wants to be deleted.
     * @param index: the index of the config that wants to be deleted.
     */
    void erased(int index);

private:
    Ui::InputListSettingsConfig *ui = nullptr;
    list<SettingsOption*> *listElements = nullptr;
    int index = 0;
};

#endif // INPUTLISTSETTINGSCONFIG_H
