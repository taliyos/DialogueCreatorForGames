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
#include <duckx.hpp>

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


    // Create a File menu
    QMenu *fileMenu = menuBar()->addMenu("File");
    QMenu *editMenu = menuBar()->addMenu("Edit");
    QMenu *importMenu;

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
    importMenu = fileMenu->addMenu("Import");
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionExit);

    importMenu->addAction(ui->actionImportTxt);
    importMenu->addAction(ui->actionImportDocx);

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
    connect(ui->actionImportTxt, &QAction::triggered, this, &MainWindow::importTxt);
    connect(ui->actionImportDocx, &QAction::triggered, this, &MainWindow::importDocx);
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
    QString fileName = QFileDialog::getSaveFileName(this, "Import txt");
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

void MainWindow::importTxt()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import txt file");
    if (fileName.split('.')[1] != QString("txt"))
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
    QListIterator<DialogueEntry> itr(textBoxes);

    while(!line.isNull())
    {
        if (line.trimmed().isEmpty())
        {
            line = in.readLine();
            continue;
        }

        QTextEdit* currentTextBox;
        if (itr.hasNext())
            currentTextBox = itr.next().textBox;
        else
        {
            this->addTextBox();
            currentTextBox = textBoxes.last().textBox;
        }

        currentTextBox->setText(line);
        line = in.readLine();
    }

    file.close();
}

void MainWindow::importDocx()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import docx file");
    if (fileName.split('.')[1] != QString("docx"))
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


    QListIterator<DialogueEntry> itr(textBoxes);
    for (auto p : doc.paragraphs())
        for (auto r : p.runs())
        {
            QString line = QString::fromStdString(r.get_text());
            if (line.trimmed().isEmpty())
                continue;

            QTextEdit* currentTextBox;
            if (itr.hasNext())
                currentTextBox = itr.next().textBox;
            else
            {
                this->addTextBox();
                currentTextBox = textBoxes.last().textBox;
            }

            currentTextBox->setText(line);
        }
}

void MainWindow::exit()
{
    QCoreApplication::quit();
}
