#ifndef NEWTAB_H
#define NEWTAB_H

#include <QWidget>

namespace Ui {
class NewTab;
}

class NewTab : public QWidget
{
    Q_OBJECT

public:
    explicit NewTab(QWidget *parent = nullptr);
    ~NewTab();

private:
    Ui::NewTab *ui;
};

#endif // NEWTAB_H
