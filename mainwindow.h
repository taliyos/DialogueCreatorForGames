#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qboxlayout.h>
#include <QSplitter>
#include <QTextEdit>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void selectFont();
    void increaseFontSize();
    void decreaseFontSize();
    void selectFontColor();
    void makeTextBold();
    void makeTextItalic();
    void underlineText();
    void newDocument();
    void open();
    void save();
    void saveAs();
    void exit();
    void generateCharacterDialogue();
    void addTextBox();
    void resizeToScreen();
    QTextEdit* currentText();
private:
    Ui::MainWindow *ui;
    QString currentFile;
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QSplitter *splitter = new QSplitter(Qt::Vertical);
    QList<QTextEdit*> textBoxes;

};
#endif // MAINWINDOW_H
