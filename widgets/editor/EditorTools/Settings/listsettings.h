#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QPushButton>
#include <QDialog>

namespace Ui {
class ListSettings;
}

class ListSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ListSettings(QWidget *parent = nullptr);
    ~ListSettings();

    // Buttons
    QPushButton* getOK();
    QPushButton* getCancel();

signals:

private slots:

private:
    Ui::ListSettings *ui;
};

#endif // LISTSETTINGS_H
