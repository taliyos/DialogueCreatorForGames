#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QPushButton>
#include <QDialog>
#include "data/Fields/fielddata.h"
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
    /**
     * @brief addOption
     */
    void addOption();
    /**
     * @brief eraseOption
     * @param index
     */
    void eraseOption(int index);
    /**
     * @brief loadOptions
     */
    void loadOptions();
    /**
     * @brief saveOptions
     */
    void saveOptions();

signals:
    void optionErased (int index);
    void optionsSaved (list<string> options);

private:
    Ui::ListSettings *ui = nullptr;
    list<string> *data = nullptr;
    list<SettingsOption*> *listElements = nullptr;

};

#endif // LISTSETTINGS_H
