#ifndef NEWTAB_H
#define NEWTAB_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class NewTab;
}

class NewTab : public QPushButton
{
    Q_OBJECT

public:
    explicit NewTab(QWidget *parent = nullptr);
    ~NewTab();

private:
    Ui::NewTab *ui;
};

#endif // NEWTAB_H
