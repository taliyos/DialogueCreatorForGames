#ifndef CLOSABLETAB_H
#define CLOSABLETAB_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ClosableTab;
}

class ClosableTab : public QPushButton
{
    Q_OBJECT

public:
    explicit ClosableTab(QWidget *parent = nullptr);
    ~ClosableTab();

    /**
     * Sets the focus value for this tab.
     * @param focus - Whether or not the tab is focused
     */
    void setFocus(bool focus);

    /**
     * Returns the current focus value.
     */
    bool hasFocus() const;

signals:

    /**
     * Emitted when the focus is changed
     * @param focus - The new focus state.
     */
    void focusChanged(bool focus);

private:
    Ui::ClosableTab *ui;

    bool focus;
};

#endif // CLOSABLETAB_H
