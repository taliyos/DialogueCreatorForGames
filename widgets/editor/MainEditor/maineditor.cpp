#include "maineditor.h"
#include "ui_maineditor.h"

MainEditor::MainEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainEditor)
{
    ui->setupUi(this);
}

MainEditor::~MainEditor()
{
    delete ui;
}
