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
    struct DialogueEntry {
        QLineEdit* characterLabel;
        QTextEdit* textBox;
        QStringList effects;
        bool autoState;
    };
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
    void importTxt();
    void importDocx();
    void importJson();
    void exportJson();
    void exit();
    void generateCharacterDialogue();
    void addTextBox();
    QTextEdit* currentText();
    QLineEdit* currentCharacter();
    bool currentAutoState();
    void updateAutoStateForCurrentText(bool state);
    QString generateHtml(const DialogueEntry& entry);
    void exportToHtml(const QString& filePath);
    void onPreviewButtonClicked();
    void selectBackgroundImage();


private:
    Ui::MainWindow *ui;
    QString currentFile;
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QSplitter *splitter = new QSplitter(Qt::Vertical);

    QList<DialogueEntry> textBoxes;


    QScrollArea* scrollArea;
    QWidget* scrollWidget;

};
#endif // MAINWINDOW_H
