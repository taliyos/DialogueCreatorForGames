#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QPushButton>
#include <QDialog>
#include "data/Fields/fielddata.h"
#include "widgets/editor/EditorTools/Settings/settingsoption.h"


namespace Ui {
class ListSettings;
}

/**
 * A Dialog representing settings for list fields.
 * Has a list of SettingsOptions that are the UI elements.
 * Has a list of strings that are the data loaded into and saved from the UI.
 */
class ListSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ListSettings(QWidget *parent = nullptr);
    ~ListSettings();

    // Buttons
    QPushButton* getOK();
    QPushButton* getCancel();

    // List methods
    /**
     * Adds an option to the UI and list elements.
     */
    void addOption();
    /**
     * Erases the option at the given index.
     * @param index: the index to erase at.
     */
    void eraseOption(int index);
    /**
     * Loads the options from the data into the UI (listElements).
     */
    void loadOptions();
    /**
     * Saves the options from the UI(listElements) into the data.
     */
    void saveOptions();

signals:
    void optionErased (int index);
    void optionsSaved (list<string> options);

private:
    Ui::ListSettings *ui = nullptr;
    list<string> *data = nullptr;
    list<SettingsOption*> *listElements = nullptr;

private:
    Ui::ListSettings* ui;
    std::list<std::string>* data;
    std::list<SettingsOption*>* listElements;

};

#endif // LISTSETTINGS_H
