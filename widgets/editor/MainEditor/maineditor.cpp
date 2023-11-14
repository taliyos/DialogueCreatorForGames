#include <QFileDialog>
#include <QMessageBox>
#include "data/Presets/preset.h"
#include "maineditor.h"
#include "ui_maineditor.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "widgets/editor/Fields/TextField/textfield.h"
#include "widgets/editor/FieldConnection/fieldconnection.h"
#include "data/ConnectionData/connectiondata.h"
#include <QWebEngineView>
#include <QDebug>
#include <qclipboard.h>

#include "widgets/editor/Fields/ListField/listfield.h"
#include "duckx.hpp"
#include <json.hpp>
#include <fstream>

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
    connect(editorTools->getCustomField1(), &QAbstractButton::clicked, this, &MainEditor::createListField);

    connect(editorTools->getListSettingsPage(), &ListSettings::optionsSaved, this, &MainEditor::updateListFields);

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

    // Connect presets
    connect(editorTools->getAddPreset(), &QAbstractButton::clicked, this, &MainEditor::createPreset);
    connect(editorTools, &EditorTools::applyPreset, this, &MainEditor::applyPreset);

    // Create first dialogue box
    createTextField();
}


void MainEditor::handlePreviewRequest(const QString& content, const QString& content2, FieldData* textData) {
    QString fullHtml;
    if (data->getFieldType() == Text || data->getFieldType() == TextCharacter)
        fullHtml = TextField::generateHtml(content, content2, (TextData*) textData);
    else if (data->getFieldType() == List)
        fullHtml = ListField::generateHtml(content, content2, (ListData*) textData);
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
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("json"))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: not a .json file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    std::ifstream f(fileName.toStdString());
    nlohmann::json j = nlohmann::json::parse(f);
    nlohmann::detail::iter_impl itr = j.begin();

    FieldData* currentField = data;

    // Iterate through each of the json values where each json value represents
    //  a FieldData object
    while(itr != j.end())
    {
        if (currentField == nullptr)
        {
            // Create a new text field (FieldData object) and call fromJson
            createTextField();
            currentField = data;
            while (currentField->getToConnection() != nullptr && currentField->getToConnection()->getNext() != nullptr)
            {
                currentField = currentField->getToConnection()->getNext();
            }
        }
        currentField->fromJson(j[itr.key()]);
        TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
        field->getTextField()->setText(QString::fromStdString(currentField->getText()));
        itr++;
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            currentField = nullptr;
    }
}

// File -> Save
// Identical to exportJson, except it uses the currentFile (current filename)
void MainEditor::on_actionSave_triggered()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        on_actionSaveAs_triggered();
        return;
    }

    fileName = currentFile;
    setWindowTitle(fileName);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);

    FieldData* currentField = data;
    nlohmann::json j;

    // For each FieldData object, create a json object
    int box_num = 1;
    while(currentField != nullptr)
    {
        string box = "text box " + std::to_string(box_num);

        // Currently, the FieldData text must be set from the text box
        TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
        QString text = field->getTextField()->text();
        currentField->setText(text.toStdString());

        nlohmann::json d = currentField->toJson();
        j[box] = d;
        box_num++;
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            currentField = nullptr;
    }

    out << QString::fromStdString(j.dump());
    file.close();


}

// File -> Save As
// Identical to exportJson except it sets currentFile
void MainEditor::on_actionSaveAs_triggered()
{
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getSaveFileName(this, "Export json file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("json"))
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

    FieldData* currentField = data;
    nlohmann::json j;

    // For each FieldData object, create a json object
    int box_num = 1;
    while(currentField != nullptr)
    {
        string box = "text box " + std::to_string(box_num);

        // Currently, the FieldData text must be set from the text box
        TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
        QString text = field->getTextField()->text();
        currentField->setText(text.toStdString());

        nlohmann::json d = currentField->toJson();
        j[box] = d;
        box_num++;
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            currentField = nullptr;
    }

    out << QString::fromStdString(j.dump());
    file.close();
}

void MainEditor::on_actionImportTxt_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import txt file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("txt"))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: not a .txt file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString line = in.readLine();
    FieldData* currentField = data;

    while(!line.isNull())
    {
        if (line.trimmed().isEmpty())
        {
            line = in.readLine();
            continue;
        }

        if (currentField == nullptr)
        {
            createTextField();
            currentField = data;
            while (currentField->getToConnection()!=nullptr && currentField->getToConnection()->getNext() != nullptr)
            {
                currentField = currentField->getToConnection()->getNext();
            }
        }

        currentField->setText(line.toStdString());
        TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
        field->getTextField()->setText(line);
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            currentField = nullptr;
        line = in.readLine();
    }

    file.close();
}

void MainEditor::on_actionImportDocx_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import docx file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("docx"))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: not a .docx file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    duckx::Document doc(fileName.toStdString());
    doc.open();

    FieldData* currentField = data;
    for (auto p : doc.paragraphs())
    {
        for (auto r : p.runs())
        {
            QString line = QString::fromStdString(r.get_text());
            if (line.trimmed().isEmpty())
                continue;

            if (currentField == nullptr)
            {
                createTextField();
                currentField = data;
                while (currentField->getToConnection()!=nullptr && currentField->getToConnection()->getNext() != nullptr)
                {
                    currentField = currentField->getToConnection()->getNext();
                }
            }

            currentField->setText(line.toStdString());
            TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
            field->getTextField()->setText(line);
            if (currentField->getToConnection() != nullptr)
                currentField = currentField->getToConnection()->getNext();
            else
                currentField = nullptr;
        }
    }
}

void MainEditor::on_actionImportJson_triggered()
{
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getOpenFileName(this, "Import Json file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("json"))
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
    nlohmann::json j = nlohmann::json::parse(f);
    nlohmann::detail::iter_impl itr = j.begin();

    FieldData* currentField = data;

    // Iterate through each of the json values where each json value represents
    //  a FieldData object
    while(itr != j.end())
    {
        if (currentField == nullptr)
        {
             // Create a new text field (FieldData object) and call fromJson
            createTextField();
            currentField = data;
            while (currentField->getToConnection() != nullptr && currentField->getToConnection()->getNext() != nullptr)
            {
                currentField = currentField->getToConnection()->getNext();
            }
        }
        currentField->fromJson(j[itr.key()]);
        TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
        field->getTextField()->setText(QString::fromStdString(currentField->getText()));
        itr++;
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            currentField = nullptr;
    }
}

void MainEditor::on_actionExportJson_triggered()
{
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getSaveFileName(this, "Export json file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("json"))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: not a .json file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream out(&file);

    FieldData* currentField = data;
    nlohmann::json j;

    // For each FieldData object, create a json object
    int box_num = 1;
    while(currentField != nullptr)
    {
        string box = "text box " + std::to_string(box_num);

        // Currently, the FieldData text must be set from the text box
        TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
        QString text = field->getTextField()->text();
        currentField->setText(text.toStdString());

        nlohmann::json d = currentField->toJson();
        j[box] = d;
        box_num++;
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            currentField = nullptr;
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
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;

    TextField* field = reinterpret_cast<TextField*>(currentField->getUi());
    QString selectedText = field->getTextField()->selectedText();

    if (!selectedText.isEmpty()) {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(selectedText);
    }
}

// Paste
void MainEditor::on_actionPaste_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;

    TextField* field = reinterpret_cast<TextField*>(currentField->getUi());
    QClipboard* clipboard = QApplication::clipboard();
    QString clipboardText = clipboard->text();

    if (!clipboardText.isEmpty()) {
        field->getTextField()->paste();
    }
}


// Cut
void MainEditor::on_actionCut_triggered()
{
    FieldData* currentField = getActiveField();
    if (currentField == nullptr)
        return;

    TextField* field = reinterpret_cast<TextField*>(currentField->getUi());
    QString selectedText = field->getTextField()->selectedText();

    if (!selectedText.isEmpty()) {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard -> setText(selectedText);
        field->getTextField()->cut();
    }
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

void MainEditor::createListField() {
    // Create a new head pointer if the data is currently null.
    if (!data) {
        ListField* listField = designer->createListField();
        data = new ListData(listField, nullptr, nullptr);

        // Connect the removeField signal to the MainEditor's removeField function so that the
        // field is removed when the remove button is clicked within the UI.
        connect(listField, &ListField::removeField, this, &MainEditor::removeListField);
        connect(listField, &ListField::previewRequested, this, &MainEditor::handlePreviewRequest);

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
    ListField* listField = designer->createListField();
    ListData* newList = new ListData(listField, nullptr, nullptr);

    // Create a connection
    ConnectionData* connection = new ConnectionData(fieldConnection, last, newList);
    last->replaceToConnection(connection);
    newList->replaceFromConnection(connection);

    // Connect the removeField signal to the MainEditor's removeField function so that the
    // field is removed when the remove button is clicked within the UI.
    connect(listField, &ListField::removeField, this, &MainEditor::removeListField);
    connect(listField, &ListField::previewRequested, this, &MainEditor::handlePreviewRequest);

    // update the list settings
    editorTools->getListSettingsPage()->saveOptions();
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

    bool changeActive = false;

    if (fieldData == lastActive) changeActive = true;

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

    if (changeActive) lastActive = data;
    
}


// TODO: THIS HAS THE SAME BODY AS THE ABOVE FUNCTION WITH A DIFFERENT ARG TYPE
// WE SHOULD MAKE ALL FIELDS INHERIT FROM A BASE FIELD
// THEN WE ONLY NEED ONE removeFieldFunction ***
void MainEditor::removeListField(ListField* field) {
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

void MainEditor::updateListFields(string txt)
{
    qDebug() << "Main Editor: Updating List Fields with : " << txt;
    // Update fields from head onward
    FieldData* currData = data;
    while (currData != nullptr)
    {
        qDebug() << "Looking at field with ID = " << currData->getFieldType();
        // check to see if this is a list field
        if (currData->getFieldType() == List)
        {
            qDebug() << "Main Editor: Updating a field";
            ((ListData*)currData)->setDelimiterAndText(baseDelimiter, txt);
            emit ((ListField*)((ListData*)currData)->getUi())->updateRequested();
        }
        // Look for more fields
        ConnectionData* toData = currData->getToConnection();
        if (toData != nullptr)
            currData = toData->getNext();
        else
            currData = nullptr;
    }
}

// Gets active text field
// If no active text field, return most recent active text field
// If no recent text field, returns nullptr
FieldData* MainEditor::getActiveField()
{
    if (data == nullptr)
        return nullptr;
    FieldData* currentField = data;
    if (currentField->getFieldType() == List)
    {
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            return lastActive;
    }
    TextField* field = reinterpret_cast <TextField*>(currentField->getUi());
    while (!field->getTextField()->hasFocus())
    {
        if (currentField->getToConnection() != nullptr)
            currentField = currentField->getToConnection()->getNext();
        else
            return lastActive;

        if (currentField->getFieldType() == List)
        {
            if (currentField->getToConnection() != nullptr)
                currentField = currentField->getToConnection()->getNext();
            else
                return lastActive;
        }
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
    field->onCharacterClicked();
}

void MainEditor::preset_createListField() {
    createListField();
}
void MainEditor::preset_createUserPromptField() {
    createTextField();
}
void MainEditor::preset_createUserListField() {
    createTextField();
}

void MainEditor::createPreset() {
    Preset* preset = new Preset(data);
    editorTools->addPreset(preset);
}

void MainEditor::on_actionImportPreset_2_triggered()
{
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getOpenFileName(this, "Import preset file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("preset"))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: not a .preset file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    std::ifstream f(fileName.toStdString());
    nlohmann::json j = nlohmann::json::parse(f);
    nlohmann::detail::iter_impl itr = j.begin();

    std::vector<FieldTypes> fieldTypes = std::vector<FieldTypes>();
    while(itr != j.end())
    {
        if (*itr == "Text")
            fieldTypes.push_back(Text);
        else if (*itr == "TextCharacter")
            fieldTypes.push_back(TextCharacter);
        else if (*itr == "List")
            fieldTypes.push_back(List);
        else if (*itr == "UserPrompt")
            fieldTypes.push_back(UserPrompt);
        else if (*itr == "UserList")
            fieldTypes.push_back(UserList);

        itr++;
    }

    Preset* preset = new Preset(fieldTypes);
    editorTools->addPreset(preset);
}

void MainEditor::on_actionExportPreset1_triggered()
{
    exportPreset(1);
}

void MainEditor::on_actionExportPreset2_triggered()
{
    exportPreset(2);
}

void MainEditor::on_actionExportPreset3_triggered()
{
    exportPreset(3);
}

void MainEditor::on_actionExportPreset4_triggered()
{
    exportPreset(4);
}


void MainEditor::exportPreset(int num)
{
    // Get json filename from Windows Explorer popup and verify it is json
    QString fileName = QFileDialog::getSaveFileName(this, "Export preset file");
    if (fileName.isEmpty() || !fileName.contains('.') || fileName.split('.')[1] != QString("preset"))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: not a .preset file");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    nlohmann::json j;

    if (editorTools->getPresets().empty())
    {
        QMessageBox::warning(this, "Warning", "Preset does not exist");
        return;
    }

    std::vector<Preset*> presets = editorTools->getPresets();
    std::vector<Preset*>::const_iterator itr = presets.begin();
    int i = 1;
    while (itr != presets.end())
    {
        if (i < num)
            itr++;
        else
            break;
    }
    if (i != num)
    {
        QMessageBox::warning(this, "Warning", "Preset does not exist");
        return;
    }
    Preset* preset = *itr;

    std::vector<FieldTypes> storage = preset->getStorage();
    list<string> types = list<string>();
    for (std::vector<FieldTypes>::iterator itr = storage.begin(); itr != storage.end(); itr++) {
        switch (*itr) {
        case Text:
            types.push_back("Text");
            break;
        case TextCharacter:
            types.push_back("TextCharacter");
            break;
        case List:
            types.push_back("List");
            break;
        case UserPrompt:
            types.push_back("UserPrompt");
            break;
        case UserList:
            types.push_back("UserList");
            break;
        }
    }

    j = types;

    out << QString::fromStdString(j.dump());
    file.close();
}

void MainEditor::applyPreset(Preset* preset) {
    preset->apply(data, this);
}
