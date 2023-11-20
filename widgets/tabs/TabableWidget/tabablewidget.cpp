#include "tabablewidget.h"
#include "ui_tabablewidget.h"

TabableWidget::TabableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabableWidget)
{
    ui->setupUi(this);
}

TabableWidget::~TabableWidget()
{
    delete ui;
}

const QString& TabableWidget::getFileName() {
    return fileName;
}
