#include "widgets/tabs/ClosableTab/closabletab.h"
#include "qstyle.h"
#include "ui_closabletab.h"

ClosableTab::ClosableTab(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::ClosableTab)
{
    ui->setupUi(this);

    id = QUuid::createUuid();

    setFocus(true);
    connect(this, &QAbstractButton::clicked, this, [this](){ setFocus(true); });
    connect(ui->close, &QAbstractButton::clicked, this, &ClosableTab::close);
}

ClosableTab::~ClosableTab()
{
    delete ui;
}

void ClosableTab::setFocus(bool focus, bool callback) {
    // Only update if the new focus is different from current
    if (this->focus == focus) return;
    this->focus = focus;

    // Updates the style property, unpolishing and polishing to refresh the UI
    setProperty("isFocus", focus);
    style()->unpolish(this);
    style()->polish(this);

    if (!callback) return;

    emit focusChanged(focus);
    if (focus) emit onFocused();
}

void ClosableTab::close() {
    emit onClose();
}

bool ClosableTab::hasFocus() const {
    return focus;
}

QUuid ClosableTab::getId() const {
    return id;
}
