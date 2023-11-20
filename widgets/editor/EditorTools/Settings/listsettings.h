#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QPushButton>
#include <QDialog>
#include "widgets/editor/EditorTools/Settings/settingsoption.h"


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
    void optionsSaved (std::string txt);

private:
    Ui::ListSettings* ui;
    std::list<std::string>* data;
    std::list<SettingsOption*>* listElements;

};

#endif // LISTSETTINGS_H
