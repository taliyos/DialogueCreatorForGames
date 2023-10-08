#ifndef DESIGNER_H
#define DESIGNER_H

#include <QWidget>

namespace Ui {
class Designer;
}

class Designer : public QWidget
{
    Q_OBJECT

public:
    explicit Designer(QWidget *parent = nullptr);
    ~Designer();

private:
    Ui::Designer *ui;
};

#endif // DESIGNER_H
