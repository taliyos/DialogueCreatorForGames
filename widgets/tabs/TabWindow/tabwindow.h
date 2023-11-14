#ifndef TABS_H
#define TABS_H

#include <QWidget>

namespace Ui {
class Tabs;
}

class Tabs : public QWidget
{
    Q_OBJECT

public:
    explicit Tabs(QWidget *parent = nullptr);
    ~Tabs();

private:
    Ui::Tabs *ui;
};

#endif // TABS_H
