#ifndef SETTINGSOPTION_H
#define SETTINGSOPTION_H
#include <QLineEdit>
#include <QWidget>

namespace Ui {
class SettingsOption;
}

class SettingsOption : public QWidget
{
    Q_OBJECT

public:
    //make a fucntion to access Qline
    explicit SettingsOption(QWidget *parent = nullptr);
    ~SettingsOption();
   QLineEdit* getLineEdit();

private:
    Ui::SettingsOption *ui;
};

#endif // SETTINGSOPTION_H
