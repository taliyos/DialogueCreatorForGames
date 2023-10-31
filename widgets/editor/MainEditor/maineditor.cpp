#include <QFileDialog>
#include <QMessageBox>
#include "maineditor.h"
#include "ui_maineditor.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "widgets/editor/Fields/TextField/textfield.h"
#include "widgets/editor/FieldConnection/fieldconnection.h"
#include "data/ConnectionData/connectiondata.h"
#include <QWebEngineView>

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
    // Assuming textField is an instance of TextField or a pointer to one in your MainEditor
    //connect(ui->preview, &TextField::previewRequested, this, &MainEditor::handlePreviewRequest);


//    QWebEngineView* webView = ui->testWebWidget;
//    webView->load(QUrl("https://qt-project.org/"));

}


void MainEditor::handlePreviewRequest(const QString& content) {
    QString fullHtml = TextField::generateHtml(content);
    QWebEngineView* view = designer->getPreview();
    view->setHtml(fullHtml);
    view->show();
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
    // Check fields

    FieldConnection* fieldConnection = designer->createFieldConnection();
    TextField* textField = designer->createTextField();

    // TEST ONLY
    FieldData* prevData = new FieldData();
    FieldData* nextData = new FieldData();

    // Add to data
    connectionData = new ConnectionData(prevData, nextData, fieldConnection);
    connect(textField, &TextField::previewRequested, this, &MainEditor::handlePreviewRequest);
    // do whatever we want with the new text field

}
