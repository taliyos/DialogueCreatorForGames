#include "effectsdropdown.h"
#include "ui_effectsdropdown.h"

EffectsDropdown::EffectsDropdown(QWidget *parent) :
    QMenu(parent),
    ui(new Ui::EffectsDropdown)
{
    ui->setupUi(this);
}

EffectsDropdown::~EffectsDropdown()
{
    delete ui;
}

void EffectsDropdown::setName(const QString name) {
    ui->dropdownName->setText(name);
}

QPushButton* EffectsDropdown::createButton(const QString name) const {
    QPushButton* button = new QPushButton();
    button->setText(name);
    button->setFocus(Qt::FocusReason::NoFocusReason);
    button->setMinimumSize(120, 45);

    QFont font = button->font();
    font.setPixelSize(15);
    button->setFont(font);

    ui->effects->addWidget(button);

    return button;
}

QPushButton* EffectsDropdown::getRemove() const { return ui->more; }
