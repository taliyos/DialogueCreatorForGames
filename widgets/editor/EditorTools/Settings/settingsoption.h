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
    explicit SettingsOption(QWidget *parent = nullptr, int index = 0);
    ~SettingsOption();
    QLineEdit* getLineEdit();
    QPushButton* getButton();
    int getIndex();
    void setIndex(int value);
    void erase();
signals:
    void erased(int index);

private:
    Ui::SettingsOption *ui = nullptr;
    int index = 0;
};

#endif // SETTINGSOPTION_H
