#include <QFileDialog>
#include <QMessageBox>
#include "maineditor.h"
#include "ui_maineditor.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "widgets/editor/Fields/TextField/textfield.h"
#include "data/Dialogue/DialogueData.h"
#include <duckx.hpp>
#include <json.hpp>
#include <fstream>

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

void MainEditor::on_actionImportTxt_triggered()
{
//    QString fileName = QFileDialog::getOpenFileName(this, "Import txt file");
//    if (fileName.split('.')[1] != QString("txt"))
//    {
//        QMessageBox::warning(this, "Warning", "Cannot open file: not a .txt file");
//        return;
//    }
//    QFile file(fileName);
//    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
//        return;
//    }

//    currentFile = fileName;
//    setWindowTitle(fileName);
//    QTextStream in(&file);
//    QString line = in.readLine();
//    QListIterator<DialogueData> itr(textBoxes);

//    while(!line.isNull())
//    {
//        if (line.trimmed().isEmpty())
//        {
//            line = in.readLine();
//            continue;
//        }

//        DialogueData* currentTextBox;
//        if (itr.hasNext())
//            currentTextBox = itr.next();
//        else
//        {
//            this->createTextField();
//            currentTextBox = textBoxes.last();
//        }

//        currentTextBox->setText(line);
//        line = in.readLine();
//    }

//    file.close();
}

void MainEditor::on_actionImportDocx_triggered()
{
//    QString fileName = QFileDialog::getOpenFileName(this, "Import docx file");
//    if (fileName.split('.')[1] != QString("docx"))
//    {
//        QMessageBox::warning(this, "Warning", "Cannot open file: not a .docx file");
//        return;
//    }
//    QFile file(fileName);
//    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
//        return;
//    }

//    duckx::Document doc(fileName.toStdString());
//    doc.open();


//    QListIterator<DialogueData> itr(textBoxes);
//    for (auto p : doc.paragraphs())
//        for (auto r : p.runs())
//        {
//            QString line = QString::fromStdString(r.get_text());
//            if (line.trimmed().isEmpty())
//                continue;

//            DialogueData* currentTextBox;
//            if (itr.hasNext())
//                currentTextBox = itr.next();
//            else
//            {
//                this->createTextField();
//                currentTextBox = textBoxes.last();
//            }

//            currentTextBox->setText(line.toStdString());
//        }
}

void MainEditor::on_actionImportJson_triggered()
{
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getOpenFileName(this, "Import Json file");
    if (fileName.split('.')[1] != QString("json"))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: not a .json file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    std::ifstream f(fileName.toStdString());
    nlohmann::json data = nlohmann::json::parse(f);
    nlohmann::detail::iter_impl itr = data.begin();

    // Sample textBoxes list, should be real list of DialogueData objects
    QList<DialogueData> textBoxes = {};
    QList<DialogueData>::Iterator d_itr = textBoxes.begin();

    // Iterate through each of the json values where each json value represents
    //  a DialogueData object
    while(itr != data.end())
    {
        if (d_itr != textBoxes.end())
        {
            d_itr->fromJson(data[itr.key()]);
            d_itr++;
        }
        else
        {
            // Create a new text field (DialogueData object) and call fromJson
        }
        itr++;
    }
}

void MainEditor::on_actionExportJson_triggered()
{
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getSaveFileName(this, "Import json file");
    if (fileName.split('.')[1] != QString("json"))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: not a .json file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);

    // For now, create a sample DialogueData object
    // There should be some QList<DialogueData> to actually use
    DialogueData test = DialogueData();
    test.setText("Test");
    test.applyFieldEffect(1);
    test.applyFieldEffect(2);
    test.applyTextEffect(0, 1, 1);
    test.applyTextEffect(2,3,2);
    QList<DialogueData> textBoxes = {test, test};
    QList<DialogueData>::Iterator itr = textBoxes.begin();
    nlohmann::json j;

    // For each DialogueData object, create a json object
    int box_num = 1;
    while(itr != textBoxes.end())
    {
        string box = "text box " + std::to_string(box_num);
        nlohmann::json data = itr->toJson();
        j[box] = data;
        box_num++;
        itr++;
    }

    out << QString::fromStdString(j.dump());
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
    TextField* textField = designer->createTextField();

    // do whatever we want with the new text field

}
