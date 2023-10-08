#ifndef EDITORTOOLS_H
#define EDITORTOOLS_H

#include <QWidget>

namespace Ui {
class EditorTools;
}

class EditorTools : public QWidget
{
    Q_OBJECT

public:
    explicit EditorTools(QWidget *parent = nullptr);
    ~EditorTools();

private:
    Ui::EditorTools *ui;
};

#endif // EDITORTOOLS_H
