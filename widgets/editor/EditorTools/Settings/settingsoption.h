#ifndef SETTINGSOPTION_H
#define SETTINGSOPTION_H
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>

namespace Ui {
class SettingsOption;
}

class SettingsOption : public QWidget
{
    Q_OBJECT

public:
    //make a fucntion to access Qline
    explicit SettingsOption(QWidget *parent = nullptr, int index = 0);
    ~SettingsOption();
    QLineEdit* getLineEdit();
    QPushButton* getButton();

private:
    Ui::SettingsOption *ui;
    int index;
};

#endif // SETTINGSOPTION_H
