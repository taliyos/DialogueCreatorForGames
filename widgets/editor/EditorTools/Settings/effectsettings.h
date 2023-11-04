#ifndef EFFECTSETTINGS_H
#define EFFECTSETTINGS_H

#include <QPushButton>
#include <QDialog>

namespace Ui {
class EffectSettings;
}

class EffectSettings : public QDialog
{
    Q_OBJECT

public:
    // constructor and destructor
    explicit EffectSettings(QWidget *parent = nullptr);
    ~EffectSettings();

    // buttons
    QPushButton* getOK();
    QPushButton* getCancel();

signals:

private slots:

private:
    Ui::EffectSettings *ui;
};

#endif // EFFECTSETTINGS_H
