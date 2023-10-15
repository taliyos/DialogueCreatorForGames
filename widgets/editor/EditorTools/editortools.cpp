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

QPushButton* EditorTools::getTextFieldButton() {
    return ui->textFieldBtn;
}

QPushButton* EditorTools::getPasteButton() {
    return ui->pasteBtn;
}

QPushButton* EditorTools::getCutButton() {
    return ui->cutBtn;
}

QPushButton* EditorTools::getCopyButton() {
    return ui->copyBtn;
}

