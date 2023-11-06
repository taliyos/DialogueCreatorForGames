#ifndef EFFECTSDROPDOWN_H
#define EFFECTSDROPDOWN_H

#include "qpushbutton.h"
#include <QMenu>

namespace Ui {
class EffectsDropdown;
}

class EffectsDropdown : public QMenu
{
    Q_OBJECT

public:
    explicit EffectsDropdown(QWidget *parent = nullptr);
    ~EffectsDropdown();

    void setName(const QString name);

    /**
     * Creates a button and adds it to the dropdown menu with the default properties.
     * @param name - A QString representing the text to be shown on the button.
     * @return The created button.
     */
    QPushButton* createButton(const QString name) const;

    QPushButton* getRemove() const;

private:
    Ui::EffectsDropdown *ui;
};

#endif // EFFECTSDROPDOWN_H
