#ifndef EDITORTABBAR_H
#define EDITORTABBAR_H

#include <QWidget>
#include <QTabBar>

namespace Ui {
class EditorTabBar;
}

class EditorTabBar : public QWidget
{
    Q_OBJECT

public:
    explicit EditorTabBar(QWidget *parent = nullptr);
    ~EditorTabBar();

    QTabBar* getTabBar();

private:
    Ui::EditorTabBar *ui;
};

#endif // EDITORTABBAR_H
