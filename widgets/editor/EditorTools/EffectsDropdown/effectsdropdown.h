#ifndef EFFECTSDROPDOWN_H
#define EFFECTSDROPDOWN_H

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

private:
    Ui::EffectsDropdown *ui;
};

#endif // EFFECTSDROPDOWN_H
