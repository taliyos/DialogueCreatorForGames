#include "widgets/tabs/ClosableTab/closabletab.h"
#include "qstyle.h"
#include "ui_closabletab.h"

ClosableTab::ClosableTab(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::ClosableTab)
{
    ui->setupUi(this);

    setFocus(true);
}

ClosableTab::~ClosableTab()
{
    delete ui;
}

void ClosableTab::setFocus(bool focus) {
    if (this->focus == focus) return;
    this->focus = focus;

    setProperty("focus", focus);
    style()->unpolish(this);
    style()->polish(this);

    emit focusChanged(focus);
}

bool ClosableTab::hasFocus() const {
    return focus;
}
