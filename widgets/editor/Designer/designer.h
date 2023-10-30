#ifndef DESIGNER_H
#define DESIGNER_H

#include <QPushButton>
#include <QWidget>
#include <QWebEngineView>
#include "../FieldConnection/fieldconnection.h"

class TextField;

namespace Ui {
class Designer;
}

class Designer : public QWidget
{
    Q_OBJECT

public:
    explicit Designer(QWidget *parent = nullptr);
    ~Designer();

    FieldConnection* createFieldConnection();
    TextField* createTextField();

    // Getters
    QPushButton* getCreateField();
    QWebEngineView* getPreview();

private:
    Ui::Designer *ui;
};

#endif // DESIGNER_H
