#include "maineditor.h"
#include "ui_maineditor.h"

MainEditor::MainEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainEditor)
{
    ui->setupUi(this);
}

MainEditor::~MainEditor()
{
    delete ui;
}
