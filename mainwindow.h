#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <qboxlayout.h>
#include <QSplitter>
#include <QTextEdit>
#include <QLineEdit>
#include <QScrollArea>
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
    void removeTextBox();
    QTextEdit* currentText();
    QLineEdit* currentCharacter();
    bool currentAutoState();
    void updateAutoStateForCurrentText(bool state);

private:
    Ui::MainWindow *ui;
    QString currentFile;
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QSplitter *splitter = new QSplitter(Qt::Vertical);

    struct DialogueEntry {
        QLineEdit* characterLabel;
        QTextEdit* textBox;
        QHBoxLayout* hLayout;
        QVBoxLayout* columnLayout;
        QStringList effects;
        bool autoState;
    };
    QList<DialogueEntry> textBoxes;


    QScrollArea* scrollArea;
    QWidget* scrollWidget;

};
#endif // MAINWINDOW_H
