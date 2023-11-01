#ifndef DESIGNER_H
#define DESIGNER_H

#include <QPushButton>
#include <QWidget>
#include "../Fields/TextField/textfield.h"
#include "../FieldConnection/fieldconnection.h"

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

    void removeWidget(QWidget* widget);

    // Getters
    QPushButton* getCreateField();

private:
    Ui::Designer *ui;
};

#endif // DESIGNER_H
