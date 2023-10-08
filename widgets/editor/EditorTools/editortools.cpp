#include "editortools.h"
#include "ui_editortools.h"

EditorTools::EditorTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorTools)
{
    ui->setupUi(this);
}

EditorTools::~EditorTools()
{
    delete ui;
}
