#include <QFileDialog>
#include <QMessageBox>
#include "maineditor.h"
#include "ui_maineditor.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "widgets/editor/Fields/TextField/textfield.h"
#include "widgets/editor/FieldConnection/fieldconnection.h"
#include "data/ConnectionData/connectiondata.h"

#include "data/Fields/MainFields/text/textdata.h"

MainEditor::MainEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainEditor)
{
    ui->setupUi(this);

    editorTools = ui->toolsWidget;
    designer = ui->designerWidget;

    connect(editorTools->getPaste(), &QAbstractButton::clicked, this, &MainEditor::on_actionPaste_triggered);
    connect(editorTools->getCut(), &QAbstractButton::clicked, this, &MainEditor::on_actionCut_triggered);
    connect(editorTools->getCopy(), &QAbstractButton::clicked, this, &MainEditor::on_actionCopy_triggered);

    connect(editorTools->getTextField(), &QAbstractButton::clicked, this, &MainEditor::createTextField);

    connect(designer->getCreateField(), &QAbstractButton::clicked, this, &MainEditor::createTextField);


    // Create first dialogue box
    createTextField();
}

MainEditor::~MainEditor()
{
    delete ui;
}


// Toolbar

// File -> Open
void MainEditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();

    /*QTextEdit* editor = this->currentText();
    if(editor) {
        editor->setText(text);
    } else {
        // If no editor is focused, use the main one
        //ui->textEdit->setText(text);
    }*/

    file.close();
}

// File -> Save
void MainEditor::on_actionSave_triggered()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    }
    else fileName = currentFile;

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Get all of the text boxes and write to file

    /* OLD, do not use
    QTextEdit* editor = this->currentText();
    QString content;
    if(editor) {
        content = editor->toPlainText();
    } else {
        // If no editor is focused, use the main one
        //content = ui->textEdit->toPlainText();
    }*/

    setWindowTitle(fileName);
    // QTextStream out(&file);
    // out << content;
    file.close();
}

// File -> Save As
void MainEditor::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As");
    QFile file (fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    if (fileName.isEmpty()) return;

    /* Old, do not use
     * QTextEdit* editor = this->currentText();
    QString content;
    if(editor) {
        content = editor->toPlainText();
    } else {
        // If no editor is focused, use the main one
        //content = ui->textEdit->toPlainText();
    }*/

    currentFile = fileName;
    setWindowTitle(fileName);
    // QTextStream out(&file);
    // out << content;
    file.close();
}


// File -> Exit
void MainEditor::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

// Copy
void MainEditor::on_actionCopy_triggered()
{

}

// Paste
void MainEditor::on_actionPaste_triggered()
{

}


// Cut
void MainEditor::on_actionCut_triggered()
{

}

// Undo
void MainEditor::on_actionUndo_triggered()
{

}

// Redo
void MainEditor::on_actionRedo_triggered()
{

}

// New file
void MainEditor::on_actionNew_triggered()
{

}

void MainEditor::createTextField() {
    // Create a new head pointer if the data is currently null.
    if (!data) {
        TextField* textField = designer->createTextField();
        data = new TextData(textField, nullptr, nullptr);
        return;
    }

    // Add a new text field with a connection if a head pointer (data) exists

    FieldData* last = data;
    while(last->getToConnection() != nullptr && last->getToConnection()->getNext() != nullptr) {
        last = last->getToConnection()->getNext();
    }

    // Create a new field connection (UI)
    FieldConnection* fieldConnection = designer->createFieldConnection();
    // Create a new text field (UI)
    TextField* textField = designer->createTextField();

    // Create a connection
    ConnectionData* connection = new ConnectionData(fieldConnection, last, nullptr);
    last->replaceToConnection(connection);

}
