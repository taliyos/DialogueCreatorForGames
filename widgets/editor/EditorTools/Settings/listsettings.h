#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QPushButton>
#include <QDialog>
#include "widgets/editor/EditorTools/Settings/settingsoption.h"

using namespace std;

namespace Ui {
class ListSettings;
}

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
    void addOption();
    void eraseOption(int index);
    void loadOptions();
    void saveOptions();

signals:
    void optionErased (int index);

private:
    Ui::ListSettings *ui;
    list<string> *data;
    list<SettingsOption*> *listElements;

};

#endif // LISTSETTINGS_H
