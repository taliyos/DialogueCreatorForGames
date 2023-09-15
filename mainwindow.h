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
