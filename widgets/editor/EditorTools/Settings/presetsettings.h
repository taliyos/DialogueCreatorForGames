#ifndef PRESETSETTINGS_H
#define PRESETSETTINGS_H

#include <QPushButton>
#include <QDialog>

namespace Ui {
class PresetSettings;
}

class PresetSettings : public QDialog
{
    Q_OBJECT

public:
    explicit PresetSettings(QWidget *parent = nullptr);
    ~PresetSettings();

    // Buttons
    QPushButton* getOK();
    QPushButton* getCancel();

signals:

private slots:

private:
    Ui::PresetSettings *ui;
};

#endif // PRESETSETTINGS_H
