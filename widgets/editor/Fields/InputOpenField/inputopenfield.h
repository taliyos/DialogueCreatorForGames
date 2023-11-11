#ifndef INPUTOPENFIELD_H
#define INPUTOPENFIELD_H

#include <QWidget>

namespace Ui {
class InputOpenField;
}

class InputOpenField : public QWidget
{
    Q_OBJECT

public:
    explicit InputOpenField(QWidget *parent = nullptr);
    ~InputOpenField();

private:
    Ui::InputOpenField *ui;
};

#endif // INPUTOPENFIELD_H
