#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>

class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr);

    QString getCharacter();
    QString getMessage();
    QString getMessageProperties();

private:
    QLineEdit *characterLineEdit;
    QLineEdit *messageLineEdit;
    QLineEdit *messagePropertiesLineEdit;
};

#endif // CUSTOMDIALOG_H
