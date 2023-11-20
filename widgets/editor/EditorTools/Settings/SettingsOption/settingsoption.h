#ifndef SETTINGSOPTION_H
#define SETTINGSOPTION_H
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>

class ListSettings;

namespace Ui {
class SettingsOption;
}
/**
 * A class representing a widget that holds an open line of text and a delete button.
 */
class SettingsOption : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsOption(QWidget *parent = nullptr, int index = 0);
    ~SettingsOption();
    QLineEdit* getLineEdit();
    QPushButton* getButton();
    int getIndex();
    void setIndex(int value);
    /**
     * Sends the erased signal out.
     */
    void erase();
signals:
    void erased(int index);

private:
    Ui::SettingsOption *ui = nullptr;
    int index = 0;
};

#endif // SETTINGSOPTION_H
