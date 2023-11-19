#ifndef FIELDSETTINGS_H
#define FIELDSETTINGS_H

#include <QDialog>

#include "widgets/editor/EditorTools/Settings/listsettings.h"
#include "widgets/editor/EditorTools/Settings/inputlistsettings.h"

using namespace std;

namespace Ui {
class FieldSettings;
}

/**
 * Extends QDialog to represent a menu that navigates between the settings pages for fields.
 */
class FieldSettings : public QDialog
{
    Q_OBJECT

public:
    explicit FieldSettings(QWidget *parent = nullptr);
    ~FieldSettings();

    ListSettings* getListSettingsPage();
    InputListSettings* getInputListSettingsPage();
    QPushButton* getInputListSettingsButton();
    QPushButton* getListSettingsButton();

    void openInputListSettings();
    void openListSettings();

private:
    Ui::FieldSettings *ui = nullptr;
    ListSettings* listSettingsPage = nullptr;
    InputListSettings* inputListSettingsPage = nullptr;
};

#endif // FIELDSETTINGS_H
