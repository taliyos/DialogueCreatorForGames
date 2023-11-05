#ifndef LISTSETTINGS_H
#define LISTSETTINGS_H

#include <QPushButton>
#include <QDialog>
#include <QLineEdit>

using namespace std;

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

    // List methods
    void addOption();
    void eraseOption(int index);
    void saveOptions();
    void loadOptions();

signals:

private slots:

private:
    Ui::ListSettings *ui;
    list<string> *data;
    list<QLineEdit*> *listElements;
};

#endif // LISTSETTINGS_H
