#ifndef CLOSABLETAB_H
#define CLOSABLETAB_H

#include <QUuid>
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
     * @param callback - Whether or not signals should be emitted
     */
    void setFocus(bool focus, bool callback = true);

    /**
     * Closes the tab, sending a close event to cleanup any
     * connected references.
     */
    void close();

    /**
     * Returns the current focus value.
     */
    bool hasFocus() const;

    /**
     * Returns the id of the tab, generated at intialization.
     */
    QUuid getId() const;

signals:

    /**
     * Emitted when the focus is changed
     * @param focus - The new focus state.
     */
    void focusChanged(bool focus);

    /**
     * Emitted when focus is enabled.
     */
    void onFocused();

    /**
     * Emitted when the tab is closed.
     */
    void onClose();

private:
    Ui::ClosableTab *ui;

    bool focus;
    QUuid id;
};

#endif // CLOSABLETAB_H
