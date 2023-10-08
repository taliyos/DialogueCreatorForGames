#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>

namespace Ui {
class MainEditor;
}

class MainEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MainEditor(QWidget *parent = nullptr);
    ~MainEditor();

private:
    Ui::MainEditor *ui;
};

#endif // MAINEDITOR_H
