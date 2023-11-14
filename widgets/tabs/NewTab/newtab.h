#ifndef NEWTAB_H
#define NEWTAB_H

#include <QToolButton>

namespace Ui {
class NewTab;
}

class NewTab : public QToolButton
{
    Q_OBJECT

public:
    explicit NewTab(QToolButton *parent = nullptr);
    ~NewTab();

private:
    Ui::NewTab *ui;
};

#endif // NEWTAB_H
