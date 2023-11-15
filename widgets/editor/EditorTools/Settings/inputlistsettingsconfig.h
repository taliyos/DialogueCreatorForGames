#ifndef INPUTLISTSETTINGSCONFIG_H
#define INPUTLISTSETTINGSCONFIG_H

#include <QDialog>

namespace Ui {
class InputListSettingsConfig;
}

class InputListSettingsConfig : public QDialog
{
    Q_OBJECT

public:
    explicit InputListSettingsConfig(QWidget *parent = nullptr);
    ~InputListSettingsConfig();

private:
    Ui::InputListSettingsConfig *ui;
};

#endif // INPUTLISTSETTINGSCONFIG_H
