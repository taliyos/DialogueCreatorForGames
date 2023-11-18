#ifndef INPUTLISTSETTINGSCONFIG_H
#define INPUTLISTSETTINGSCONFIG_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "widgets/editor/EditorTools/Settings/settingsoption.h"

using namespace std;

class InputListSettings;

namespace Ui {
class InputListSettingsConfig;
}

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
    void addOption();
    void eraseOption(int index);
    void setOptionText(list<string> options);
    const list<string> getOptionText();
    void updateUI();

    void erase();

signals:
    void erased(int index);

private:
    Ui::InputListSettingsConfig *ui = nullptr;
    list<SettingsOption*> *listElements = nullptr;
    int index = 0;
};

#endif // INPUTLISTSETTINGSCONFIG_H
