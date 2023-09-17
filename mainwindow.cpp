#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent) : 
    QMainWindow(parent), 
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    // Create a File menu
    QMenu *fileMenu = menuBar()->addMenu("File");

    // Add actions to the File menu
    fileMenu->addAction(ui->actionNew);
    fileMenu->addAction(ui->actionOpen);
    fileMenu->addAction(ui->actionSave);
    fileMenu->addAction(ui->actionSave_As);
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionExit);
    //abc
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


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::underlineText()
{
    QTextCharFormat format;
    format.setFontUnderline(!ui->textEdit->currentCharFormat().fontUnderline());
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::makeTextBold()
{
    QTextCharFormat format;
    format.setFontWeight(ui->textEdit->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::makeTextItalic()
{
    QTextCharFormat format;
    format.setFontItalic(!ui->textEdit->currentCharFormat().fontItalic());
    ui->textEdit->mergeCurrentCharFormat(format);
}


void MainWindow::selectFontColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose a color");
    if (color.isValid()) {
        // Assuming 'textEdit' is the QTextEdit object where you want to apply the color
        QTextCharFormat format;
        format.setForeground(color);
        ui->textEdit->mergeCurrentCharFormat(format);
    }
}

void MainWindow::selectFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        ui->textEdit->setFont(font);
    } else {
        // User cancelled font selection, do nothing
    }
}

void MainWindow::increaseFontSize()
{
    QFont currentFont = ui->textEdit->font();
    currentFont.setPointSize(currentFont.pointSize() + 1);
    ui->textEdit->setFont(currentFont);
}

void MainWindow::decreaseFontSize()
{
    QFont currentFont = ui->textEdit->font();
    currentFont.setPointSize(currentFont.pointSize() - 1);
    ui->textEdit->setFont(currentFont);
}

void MainWindow::newDocument()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
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
    setWindowTitle(fileName);
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
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
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
}

void MainWindow::exit()
{
    QCoreApplication::quit();
}
