#ifndef SETTINGSOPTION_H
#define SETTINGSOPTION_H
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>

class ListSettings;

namespace Ui {
class SettingsOption;
}

class SettingsOption : public QWidget
{
    Q_OBJECT

public:
    //make a fucntion to access Qline
    explicit SettingsOption(QWidget *parent = nullptr, int index = 0, ListSettings *listParent = nullptr);
    ~SettingsOption();
    QLineEdit* getLineEdit();
    QPushButton* getButton();
    void erase();

private:
    Ui::SettingsOption *ui;
    ListSettings* listParent;
    int index;
};

#endif // SETTINGSOPTION_H
