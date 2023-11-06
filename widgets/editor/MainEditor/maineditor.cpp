#include <QFileDialog>
#include <QMessageBox>
#include "maineditor.h"
#include "ui_maineditor.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "widgets/editor/Fields/TextField/textfield.h"
#include "widgets/editor/FieldConnection/fieldconnection.h"
#include "data/ConnectionData/connectiondata.h"
#include <QWebEngineView>
#include <QDebug>

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
    connect(editorTools->getCustomField1(), &QAbstractButton::clicked, this, &MainEditor::removeHead);

    connect(designer->getCreateField(), &QAbstractButton::clicked, this, &MainEditor::createTextField);

    typedef std::function<void ()> EffectFunc;
    typedef std::pair<std::string, EffectFunc> EffectPair;
    typedef std::vector<EffectPair> EffectsVector;
    EffectsVector displayEffects;
    EffectsVector characterEffects;
    EffectsVector modifierEffects;

    EffectPair wobbleField = EffectPair(std::string("Wobble"), std::bind(&MainEditor::on_actionWobble_triggered, this));
    EffectPair speedupField = EffectPair(std::string("Speedup"), std::bind(&MainEditor::on_actionSpeedup_triggered, this));
    EffectPair enlargeField = EffectPair(std::string("Enlarge"), std::bind(&MainEditor::on_actionEnlarge_triggered, this));
    EffectPair boldField = EffectPair(std::string("Bold"), std::bind(&MainEditor::on_actionBold_triggered, this));
    EffectPair typedField = EffectPair(std::string("Typed"), std::bind(&MainEditor::on_actionTyped_triggered, this));

    EffectPair wobbleText = EffectPair(std::string("Wobble"), std::bind(&MainEditor::on_actionWobbleText_triggered, this));
    EffectPair speedupText = EffectPair(std::string("Speedup"), std::bind(&MainEditor::on_actionSpeedupText_triggered, this));
    EffectPair enlargeText = EffectPair(std::string("Enlarge"), std::bind(&MainEditor::on_actionEnlargeText_triggered, this));
    EffectPair boldText = EffectPair(std::string("Bold"), std::bind(&MainEditor::on_actionBoldText_triggered, this));


    displayEffects.push_back(wobbleField);
    displayEffects.push_back(typedField);
    displayEffects.push_back(speedupField);
    displayEffects.push_back(enlargeField);
    displayEffects.push_back(boldField);

    characterEffects.push_back(enlargeText);
    characterEffects.push_back(wobbleText);
    characterEffects.push_back(boldText);
    modifierEffects.push_back(speedupText);

    editorTools->populateDisplayEffects(displayEffects);
    editorTools->populateCharacterEffects(characterEffects);
    editorTools->populateModifierEffects(modifierEffects);

    connect(editorTools->getDisplayDropdown()->getRemove(), &QAbstractButton::clicked, this, &MainEditor::on_actionRemoveFieldEffect_triggered);
    connect(editorTools->getCharacterDropdown()->getRemove(), &QAbstractButton::clicked, this, &MainEditor::on_actionRemoveEffect_triggered);
    connect(editorTools->getModifierDropdown()->getRemove(), &QAbstractButton::clicked, this, &MainEditor::on_actionRemoveEffect_triggered);

    // Create first dialogue box
    createTextField();
}


void MainEditor::handlePreviewRequest(const QString& content, const QString& content2, TextData* textData) {
    QString fullHtml = TextField::generateHtml(content, content2, textData);
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

void MainEditor::on_actionWobble_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    currentField->addOrRemoveFieldEffect(1);
  }

void MainEditor::on_actionEnlarge_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    currentField->addOrRemoveFieldEffect(2);
}

void MainEditor::on_actionSpeedup_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    currentField->addOrRemoveFieldEffect(3);
}

void MainEditor::on_actionBold_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    currentField->addOrRemoveFieldEffect(4);
}

void MainEditor::on_actionTyped_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    currentField->addOrRemoveFieldEffect(5);
}

void MainEditor::on_actionRemoveFieldEffect_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    for (int i = 1; i <= 5; i++)
    {
        currentField->removeFieldEffect(i);
    }
}

void MainEditor::on_actionWobbleText_triggered()
{
    applyTextEffect(1);
}

void MainEditor::on_actionEnlargeText_triggered()
{
    applyTextEffect(2);
}

void MainEditor::on_actionSpeedupText_triggered()
{
    applyTextEffect(3);
}

void MainEditor::on_actionBoldText_triggered()
{
    applyTextEffect(4);
}

void MainEditor::on_actionTypedText_triggered()
{
    applyTextEffect(5);
}

void MainEditor::applyTextEffect(int tag)
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
    if (!field->getTextField()->hasSelectedText())
        return;

    int start = field->getTextField()->selectionStart();
    int end = field->getTextField()->selectionEnd();

    if (currentField->hasTextEffect(start, end, tag))
    {
        qDebug() << "already exists";
        return;
    }

    currentField->addOrRemoveTextEffect(start, end, tag);
}

void MainEditor::on_actionRemoveEffect_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;
    TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
    if (!field->getTextField()->hasSelectedText())
        return;

    int start = field->getTextField()->selectionStart();
    int end = field->getTextField()->selectionEnd();
    for (int i = 1; i <= 5; i++)
    {
        if (currentField->hasTextEffect(start, end, i))
        {
            qDebug() << "test";
            currentField->removeTextEffect(start,end,i);
            return;
        }
    }
}

void MainEditor::createTextField() {
    // Create a new head pointer if the data is currently null.
    if (!data) {
        TextField* textField = designer->createTextField();
        data = new TextData(textField, nullptr, nullptr);

        // Connect the removeField signal to the MainEditor's removeField function so that the
        // field is removed when the remove button is clicked within the UI.
        connect(textField, &TextField::removeField, this, &MainEditor::removeField);
        connect(textField, &TextField::previewRequested, this, &MainEditor::handlePreviewRequest);

        lastActive = data;
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
    TextData* newText = new TextData(textField, nullptr, nullptr);

    // Create a connection
    ConnectionData* connection = new ConnectionData(fieldConnection, last, newText);
    last->replaceToConnection(connection);
    newText->replaceFromConnection(connection);

    // Connect the removeField signal to the MainEditor's removeField function so that the
    // field is removed when the remove button is clicked within the UI.
    connect(textField, &TextField::removeField, this, &MainEditor::removeField);
    connect(textField, &TextField::previewRequested, this, &MainEditor::handlePreviewRequest);
}

void MainEditor::removeHead() {
    if (data == nullptr) return;

    FieldData* newHead = nullptr;

    // Find the new head, if one exists
    if (data->getToConnection()) {
        newHead = data->getToConnection()->getNext();
        newHead->replaceFromConnection(nullptr);
    }

    // Remove UI widgets
    designer->removeWidget(data->getUi());

    if (data->getToConnection()) {
        designer->removeWidget(data->getToConnection()->getUi());
        delete data->getToConnection();
    }

    // Delete contained data
    delete data;

    // Set the new head
    data = newHead;
}

void MainEditor::removeField(TextField* field) {
    FieldData* fieldData = field->getData();
    ConnectionData* fromConnection = fieldData->getFromConnection();
    ConnectionData* toConnection = fieldData->getToConnection();

    // STEP 1) Reconfigure connections to remove references to fieldData

    // Modify the head if the field is the current head of the data field container
    // The fromConnection is maintained while the toConnection is removed.
    if (!fromConnection) {
        if (fieldData != data) {
            qWarning("This field is part of a detatched head.");
            return;
        }

        // Assign a new head
        if (toConnection) {
            data = toConnection->getNext();
            data->replaceFromConnection(nullptr);
        }
        else data = nullptr;
    }

    // Re-assign the fromConnection
    else if (fromConnection) {
        if (toConnection) {
            fromConnection->replaceNext(toConnection->getNext());
            toConnection->getNext()->replaceFromConnection(fromConnection);
        }
        else {
            // REMOVE FROM CONNECTION
            fromConnection->getPrevious()->replaceToConnection(nullptr);

            designer->removeWidget(fromConnection->getUi());
            delete fromConnection;
        }
    }

    // Remove the toConnection
    if (toConnection) {
        designer->removeWidget(toConnection->getUi());
        delete toConnection;
    }

    // STEP 2) Cleanup and free memory
    designer->removeWidget(field);
    delete fieldData;
    
}

// Gets active text field
// If no active text field, return most recent active text field
// If no recent text field, returns nullptr
FieldData* MainEditor::getActiveField()
{
    if (data == nullptr)
        return nullptr;
    FieldData* currentField = data;
    TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
    while (!field->getTextField()->hasFocus())
    {
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            return lastActive;

        field = reinterpret_cast <TextField*>(currentField->getUi());
    }

    lastActive = currentField;
    return currentField;
}

void MainEditor::preset_createTextField() {
    createTextField();
}
void MainEditor::preset_createTextFieldAndCharacter() {
    createTextField();
    FieldData* curr = data;
    while (curr->getToConnection()) {
        curr = curr->getToConnection()->getNext();
    }
    TextField* field = reinterpret_cast<TextField*>(curr->getUi());
    field->addCharacterWidget();
}

void MainEditor::preset_createListField() {
    createTextField();
}
void MainEditor::preset_createUserPromptField() {
    createTextField();
}
void MainEditor::preset_createUserListField() {
    createTextField();
}
