#ifndef INPUTLISTSETTINGS_H
#define INPUTLISTSETTINGS_H

#include <QDialog>

namespace Ui {
class InputListSettings;
}

class InputListSettings : public QDialog
{
    Q_OBJECT

public:
    explicit InputListSettings(QWidget *parent = nullptr);
    ~InputListSettings();

private:
    Ui::InputListSettings *ui;
};

#endif // INPUTLISTSETTINGS_H
