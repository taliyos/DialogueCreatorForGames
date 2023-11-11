#ifndef INPUTLISTFIELD_H
#define INPUTLISTFIELD_H

#include <QWidget>

namespace Ui {
class InputListField;
}

class InputListField : public QWidget
{
    Q_OBJECT

public:
    explicit InputListField(QWidget *parent = nullptr);
    ~InputListField();

private:
    Ui::InputListField *ui;
};

#endif // INPUTLISTFIELD_H
