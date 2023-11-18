#ifndef FIELDSETTINGS_H
#define FIELDSETTINGS_H

#include <QDialog>

#include "widgets/editor/EditorTools/Settings/listsettings.h"
#include "widgets/editor/EditorTools/Settings/inputlistsettings.h"

using namespace std;

namespace Ui {
class FieldSettings;
}

class FieldSettings : public QDialog
{
    Q_OBJECT

public:
    explicit FieldSettings(QWidget *parent = nullptr);
    ~FieldSettings();

    void setHead(FieldData *head);

    ListSettings* getListSettingsPage();
    InputListSettings* getInputListSettingsPage();
    QPushButton* getInputListSettingsButton();
    QPushButton* getListSettingsButton();

    void openInputListSettings();
    void openListSettings();

signals:
    void listFieldUpdateRequested(string txt);

private:
    Ui::FieldSettings *ui = nullptr;
    FieldData *head = nullptr;
    ListSettings* listSettingsPage = nullptr;
    InputListSettings* inputListSettingsPage = nullptr;
};

#endif // FIELDSETTINGS_H
