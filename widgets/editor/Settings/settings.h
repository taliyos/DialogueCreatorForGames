#ifndef SETTINGS_H
#define SETTINGS_H
#include <QLineEdit>
#include <QCheckBox>
#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

    QLineEdit* getLineEdit();
    QCheckBox* getCheckBox();

public:
    explicit Settings(QWidget *parent = nullptr);
    bool showSettings();
    bool hideSettings();
    ~Settings();
private:
    Ui::Settings *ui;
};
#endif // SETTINGS_H
