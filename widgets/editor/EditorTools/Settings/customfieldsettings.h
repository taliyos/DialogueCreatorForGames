#ifndef CUSTOMFIELDSETTINGS_H
#define CUSTOMFIELDSETTINGS_H

#include <QDialog>

namespace Ui {
class CustomFieldSettings;
}

class CustomFieldSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CustomFieldSettings(QWidget *parent = nullptr);
    ~CustomFieldSettings();

private:
    Ui::CustomFieldSettings *ui;
};

#endif // CUSTOMFIELDSETTINGS_H
