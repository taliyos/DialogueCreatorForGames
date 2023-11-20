#include "editorwindow.h"
#include "ui_editorwindow.h"

EditorWindow::EditorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
}

EditorWindow::~EditorWindow()
{
    delete ui;
}
