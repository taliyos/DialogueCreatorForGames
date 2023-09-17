#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
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
private:
    Ui::MainWindow *ui;
    QString currentFile;
};
#endif // MAINWINDOW_H
