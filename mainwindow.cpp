#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CustomDialog.h"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QSplitter>
#include <QScreen>
#include <QGuiApplication>
#include <QWindow>
#include <QApplication>
#include <QRadioButton>
#include <QButtonGroup>
#include <QScrollArea>
#include <QTimer>
#include <QButtonGroup>
#include <QDebug>
#include <qdesktopservices.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : 
    QMainWindow(parent), 
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    scrollWidget = new QWidget();
    verticalLayout = new QVBoxLayout(scrollWidget);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);

    setCentralWidget(scrollArea);
    ui->verticalLayout = verticalLayout;

    setCentralWidget(scrollArea);

    int screenWidth = QGuiApplication::primaryScreen()->geometry().width();
    scrollWidget->setFixedWidth(screenWidth / 2);

    for (int i=1; i<5; i++){
        addTextBox();
    }
    // remove one text box
    removeTextBox();


    // Create a File menu
    QMenu *fileMenu = menuBar()->addMenu("File");
    QMenu *editMenu = menuBar()->addMenu("Edit");

    QAction *undoAction = new QAction("Undo", this);
    QAction *redoAction = new QAction("Redo", this);
    QAction *copyAction = new QAction("Copy", this);
    QAction *pasteAction = new QAction("Paste", this);

    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    // Add actions to the File menu
    fileMenu->addAction(ui->actionNew);
    fileMenu->addAction(ui->actionOpen);
    fileMenu->addAction(ui->actionSave);
    fileMenu->addAction(ui->actionSave_As);
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionExit);

    // Connect actions to slots
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);
    connect(ui->actionFont, &QAction::triggered, this, &MainWindow::selectFont);
    connect(ui->actionIncrease_Font_Size, &QAction::triggered, this, &MainWindow::increaseFontSize);
    connect(ui->actionDecrease_Font_Size, &QAction::triggered, this, &MainWindow::decreaseFontSize);
    connect(ui->actionFont_Color, &QAction::triggered, this, &MainWindow::selectFontColor);
    connect(ui->actionBold, &QAction::triggered, this, &MainWindow::makeTextBold);
    connect(ui->actionItalic, &QAction::triggered, this, &MainWindow::makeTextItalic);
    connect(ui->actionUnderline, &QAction::triggered, this, &MainWindow::underlineText);
    connect(ui->actionaddCharacter, &QAction::triggered, this, &MainWindow::generateCharacterDialogue);
    //connect(undoAction, &QAction::triggered, ui->textEdit, &QTextEdit::undo);
    //connect(redoAction, &QAction::triggered, ui->textEdit, &QTextEdit::redo);
    connect(ui->actionAddTextBox, &QAction::triggered, this, &MainWindow::addTextBox);
    connect(ui->actionRemoveTextBox, &QAction::triggered, this, &MainWindow::removeTextBox);
    connect(ui->actionHTMLexport, &QAction::triggered, this, &MainWindow::onPreviewButtonClicked);
    connect(ui->actionSelectBackgroundImage, &QAction::triggered, this, &MainWindow::selectBackgroundImage);

}

QString backgroundImageFilePath;

void MainWindow::selectBackgroundImage() {
    backgroundImageFilePath = QFileDialog::getOpenFileName(this, "Select Background Image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (!backgroundImageFilePath.isEmpty()) {
        // Optionally, show a preview or a confirmation message.
        QMessageBox::information(this, "Image Selected", "Background image selected successfully!");
    }
}


void MainWindow::onPreviewButtonClicked() {
    // Temporary file path
    QString tempFilePath = QDir::tempPath() + "/preview.html";

    exportToHtml(tempFilePath);

    QDesktopServices::openUrl(QUrl::fromLocalFile(tempFilePath));
}


QString MainWindow::generateHtml(const DialogueEntry& entry) {
    QString htmlContent;

    // Add the character label to the HTML as a small box
    htmlContent += "<div style='border:1px solid black; padding:5px; width:100px; display:inline-block;'>";
    htmlContent += entry.characterLabel->text();
    htmlContent += "</div><br>";

    // Add the text box content to the HTML
    htmlContent += entry.textBox->toHtml() + "<br>";

    return htmlContent;
}

void MainWindow::exportToHtml(const QString& filePath) {
    QString fullHtml;

    // Convert image to Base64
    QString base64Image;
    if (!backgroundImageFilePath.isEmpty()) {
        QFile imageFile(backgroundImageFilePath);
        if (imageFile.open(QIODevice::ReadOnly)) {
            base64Image = QString::fromLatin1(imageFile.readAll().toBase64());
            imageFile.close();
        }
    }

    // Start HTML document
    fullHtml += "<!DOCTYPE html>";
    fullHtml += "<html><head><title>Exported Dialogue</title>";

    // Add CSS for cloud-like dialogue boxes and animations
    fullHtml += R"(
    <style>
        body {
            background-image: url('data:image/jpg;base64,)" + base64Image + R"(');
            background-size: contain;  // This will ensure the background image maintains its aspect ratio.
            background-repeat: no-repeat; // Ensures the image isn't repeated.
            background-position: center center;  // This centers the background image both horizontally and vertically.
            font-family: Arial, sans-serif;
            height: 100vh;  // This ensures the body covers the full viewport height.
            display: flex;
            align-items: center;  // Vertically centers the dialogue-container.
            justify-content: center;
        }
        .dialogue-container {
            position: relative;
            width: 350px;
            height: 150px; //  cloud height
        }
        .dialogue-box {
            display: none;
            align-items: center;
            justify-content: center;
            text-align: center;
            position: absolute;
            top: 0;
            left: 20%; // Centers the cloud
            background:#ECEFF1;
            background-color:white;
            border-radius: 100px; // Rounded corners for cloud-like appearance
            padding: 20px;
            width: 350px;
            height:120px;
            opacity: 0;
            animation: fadeInOut 4s forwards;
            box-shadow: 10px 10px rgba(0,0,0,0.2);
            margin: 0 auto;
        }
        @keyframes fadeInOut {
            0%   { opacity: 0; }
            50%  { opacity: 1; }
            100% { opacity: 0; }
        }
    </style>
    )";

    // Begin body and container
    fullHtml += "</head><body>";
    fullHtml += "<div class='dialogue-container'>";

    // Generate the HTML content for each dialogue box
    for (int i = 0; i < textBoxes.count(); ++i) {
        fullHtml += R"(<div class="dialogue-box" id="entry)" + QString::number(i) + R"(">)";
        fullHtml += textBoxes[i].textBox->toHtml();
        fullHtml += "</div>";
    }

    // Close dialogue container
    fullHtml += "</div>";

    QStringList autoStatesList;
    for (int i = 0; i < textBoxes.count(); ++i) {
        autoStatesList.append(textBoxes[i].autoState ? "true" : "false");
    }
    QString autoStatesArray = "[" + autoStatesList.join(",") + "]";

    // JavaScript for animations and looping
    fullHtml += R"(
    <script>
        let currentIndex = -1; // start with -1 so that the first dialogue is shown on the initial call
        let autoStates = )" + autoStatesArray + R"(;
        let totalDialogues = autoStates.length;

        function resetDialogues() {
            for (let i = 0; i < totalDialogues; i++) {
                let elem = document.getElementById('entry' + i);
                elem.style.opacity = '0';
                elem.style.display = 'none';
            }
        }

        function showNextDialogue() {
            // Hide current dialogue (if any)
            if (currentIndex >= 0) {
                let currentBox = document.getElementById('entry' + currentIndex);
                currentBox.style.opacity = '0';
                setTimeout(() => currentBox.style.display = 'none', 2000); // set display none after fade-out is complete
            }

            currentIndex++;

            if (currentIndex >= totalDialogues) {
                currentIndex = 0;
            }

            if (autoStates[currentIndex]) {
                let nextBox = document.getElementById('entry' + currentIndex);
                nextBox.style.display = 'flex';
                setTimeout(() => nextBox.style.opacity = '1', 100);  // Short delay to ensure display change is detected
            }
        }

        setInterval(showNextDialogue, 4000); // we're using the full animation time here to ensure the fade out is complete

        window.onload = showNextDialogue;
    </script>


)";


    // Close HTML body and document
    fullHtml += "</body></html>";

    // Save the constructed HTML to file
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << fullHtml;
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Failed to save HTML file.");
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

QTextEdit* MainWindow::currentText()
{
    QWidget* widget = QApplication::focusWidget();

    if (widget) {
        for (const DialogueEntry& entry : textBoxes) {
            if (entry.textBox == widget) {
                return entry.textBox;
            }
        }
    }
    return nullptr;
}

QLineEdit* MainWindow::currentCharacter()
{
    QWidget* widget = QApplication::focusWidget();

    if (widget) {
        for (const DialogueEntry& entry : textBoxes) {
            if (entry.textBox == widget) {
                return entry.characterLabel;
            }
        }
    }
    return nullptr;
}

bool MainWindow::currentAutoState()
{
    QWidget* widget = QApplication::focusWidget();

    if (widget) {
        for (const DialogueEntry& entry : textBoxes) {
            if (entry.textBox == widget) {
                return entry.autoState;
            }
        }
    }
    return false;
}

void MainWindow::updateAutoStateForCurrentText(bool newState)
{
    QTextEdit* current = currentText();
    if (current) {
        for (DialogueEntry& entry : textBoxes) {
            if (entry.textBox == current) {
                entry.autoState = newState;
                break;
            }
        }
    }
    QMessageBox::warning(this, "Status", "Change Success");
}

void MainWindow::addTextBox()
{
    QLineEdit* labelBox = new QLineEdit(this);
    QTextEdit* textBox = new QTextEdit(this);
    labelBox->setStyleSheet("border: 1px solid gray; border-radius: 10px;");
    textBox->setStyleSheet("border: 1px solid gray");
    textBox->raise();

    textBox->setFixedSize(QSize(550, 150));

    labelBox->setText("character: ");

    // Create the "Effect" button
    QPushButton *effectButton = new QPushButton("Effect", this);
    connect(effectButton, &QPushButton::clicked, this, [=](){
        // Handle the Effect button click here
    });

    // Create the "Preview" button
    QPushButton *previewButton = new QPushButton("Preview", this);
    connect(previewButton, &QPushButton::clicked, this, [=](){
        // Handle the Preview button click here
    });

    // Vertical layout for labelBox and textBox + buttons
    QVBoxLayout* columnLayout = new QVBoxLayout;

    // Add horizontal spacing before the labelBox
    QHBoxLayout* labelBoxLayout = new QHBoxLayout;
    QSpacerItem* LhorizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* RhorizontalSpacer = new QSpacerItem(500, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    labelBoxLayout->addSpacerItem(LhorizontalSpacer);
    labelBoxLayout->addWidget(labelBox,3);
    labelBoxLayout->addSpacerItem(RhorizontalSpacer);

    columnLayout->addLayout(labelBoxLayout);

    // Horizontal layout for textBox with effect and preview buttons
    QHBoxLayout* textBoxLayout = new QHBoxLayout;
    textBoxLayout->addWidget(effectButton);
    textBoxLayout->addWidget(textBox, 3);
    textBoxLayout->addWidget(previewButton);

    // Add textBoxLayout to the column layout
    columnLayout->addLayout(textBoxLayout);

    // Create line separator
    QFrame* line = new QFrame(this);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setMinimumHeight(50);

    // Create Auto radio buttons and button group
    QRadioButton* autoButton = new QRadioButton("Auto", this);
    autoButton->setChecked(true);
    QButtonGroup* autoGroup = new QButtonGroup(this);
    autoGroup->addButton(autoButton);
    autoGroup->setExclusive(false);

    // Horizontal layout to contain line and radio button
    QSpacerItem* LhorizontalSpacer1 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* RhorizontalSpacer1 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addSpacerItem(LhorizontalSpacer1);
    hLayout->addWidget(line);
    hLayout->addWidget(autoButton);
    hLayout->addSpacerItem(RhorizontalSpacer1);

    // Add columnLayout and hLayout to the main vertical layout
    ui->verticalLayout->addLayout(columnLayout);
    ui->verticalLayout->addLayout(hLayout);

    QStringList effectsList;

    DialogueEntry entry;
    entry.columnLayout = columnLayout;
    entry.hLayout = hLayout;
    entry.characterLabel = labelBox;
    entry.textBox = textBox;
    entry.effects = effectsList;
    entry.autoState = autoButton->isChecked();
    textBoxes.append(entry);

    connect(autoButton, &QRadioButton::toggled, [this, autoButton](bool isChecked) {
        if (!isChecked) {
            autoButton->setChecked(false);
            updateAutoStateForCurrentText(false);
        } else updateAutoStateForCurrentText(true);
    });

}

// TODO: Check if this is the way we want to handle the effects, preview, or auto buttons. ***
// This is broken, I think we need direct references to the objects we want to delete.
void MainWindow::removeTextBox ()
{
    // Check to see if we can remove
    if (textBoxes.isEmpty())
        return;
    // Pop the last text box entry
    DialogueEntry entry = textBoxes.takeLast();

    // Delete the layout items
    entry.characterLabel->deleteLater();
    entry.textBox->deleteLater();
    for (QObject * q : entry.columnLayout->children())
    {
        entry.columnLayout->removeItem((QLayoutItem*)q);
        entry.columnLayout->removeWidget((QWidget*)q);
        q->deleteLater();
    }
    entry.columnLayout->deleteLater();
    for (QObject * q : entry.hLayout->children())
    {
        entry.hLayout->removeItem((QLayoutItem*)q);
        entry.hLayout->removeWidget((QWidget*)q);
        q->deleteLater();
    }
    entry.hLayout->deleteLater();

    // Old version without preview, effects, and auto deleted
    // We can't climb the hierarchy to access columnLayout or hLayout, it causes the screen to go blank
    //entry.characterLabel->deleteLater();
    //entry.textBox->deleteLater();

    // Old version where we look through children and delete them first.
    /*
    // Delete the entry's text box and its children
    for (QObject * q : entry.textBox->children())
    {
        ui->verticalLayout->removeItem((QLayoutItem *)q);
        q->deleteLater();
    }
    ui->verticalLayout->removeItem((QLayoutItem*)entry.textBox);
    entry.textBox->deleteLater();

    // Delete the entry's character label and its children
    for (QObject * q : entry.characterLabel->children())
    {
        ui->verticalLayout->removeItem((QLayoutItem *)q);
        q->deleteLater();
    }
    ui->verticalLayout->removeItem((QLayoutItem*)entry.characterLabel);
    entry.characterLabel->deleteLater();
    */
}


void MainWindow::generateCharacterDialogue() {
    CustomDialog dialog(this);
    QTextEdit* editor = this->currentText();
    if (dialog.exec() == QDialog::Accepted) {
        QString character = dialog.getCharacter();
        QString message = dialog.getMessage();
        QString messageProperties = dialog.getMessageProperties();

        QString formattedText = QString("%1:\n{\n\tmessage: \"%2\",\n\tmessageProperties: \"%3\"\n}\n")
                                    .arg(character)
                                    .arg(message)
                                    .arg(messageProperties);

        editor->insertPlainText(formattedText);
    }
}

void MainWindow::underlineText()
{
    QTextEdit* editor = this->currentText();
    if(editor) {
        QTextCursor cursor = editor->textCursor();

        if(cursor.hasSelection()) {
            QTextCharFormat format = cursor.charFormat();

            if(format.fontWeight() == QFont::Bold) {
                format.setFontUnderline(true);
                cursor.mergeCharFormat(format);
                editor->setTextCursor(cursor);
            }
        }
    }
}

void MainWindow::makeTextBold()
{
    QTextEdit* editor = this->currentText();
    if(editor) {
        QTextCharFormat format;
        format.setFontWeight(editor->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
        editor->mergeCurrentCharFormat(format);
    }
}

void MainWindow::makeTextItalic()
{
    QTextEdit* editor = this->currentText();
    if(editor) {
        QTextCharFormat format;
        format.setFontItalic(!editor->currentCharFormat().fontItalic());
        editor->mergeCurrentCharFormat(format);
    }
}



void MainWindow::selectFontColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose a color");
    if (color.isValid()) {
        QTextEdit* editor = this->currentText();
        if(editor) {
            QTextCharFormat format;
            format.setForeground(color);
            editor->mergeCurrentCharFormat(format);
        }
    }
}

void MainWindow::selectFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        QTextEdit* editor = this->currentText();
        if(editor) {
            editor->setFont(font);
        }
    } else {
        // User cancelled font selection, do nothing
    }
}


void MainWindow::increaseFontSize()
{
    QTextEdit* editor = this->currentText();
    if(editor) {
        QFont currentFont = editor->font();
        currentFont.setPointSize(currentFont.pointSize() + 1);
        editor->setFont(currentFont);
    }
}

void MainWindow::decreaseFontSize()
{
    QTextEdit* editor = this->currentText();
    if(editor) {
        QFont currentFont = editor->font();
        currentFont.setPointSize(currentFont.pointSize() - 1);
        editor->setFont(currentFont);
    }
}


void MainWindow::newDocument()
{
    QTextEdit* editor = this->currentText();
    if(editor) {
        currentFile.clear();
        editor->setText(QString());
    }
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();

    QTextEdit* editor = this->currentText();
    if(editor) {
        editor->setText(text);
    } else {
        // If no editor is focused, use the main one
        //ui->textEdit->setText(text);
    }

    file.close();
}

void MainWindow::save()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextEdit* editor = this->currentText();
    QString content;
    if(editor) {
        content = editor->toPlainText();
    } else {
        // If no editor is focused, use the main one
        //content = ui->textEdit->toPlainText();
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    out << content;
    file.close();
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextEdit* editor = this->currentText();
    QString content;
    if(editor) {
        content = editor->toPlainText();
    } else {
        // If no editor is focused, use the main one
        //content = ui->textEdit->toPlainText();
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    out << content;
    file.close();
}


void MainWindow::exit()
{
    QCoreApplication::quit();
}
