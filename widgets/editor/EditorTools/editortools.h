#ifndef EDITORTOOLS_H
#define EDITORTOOLS_H

#include "qpushbutton.h"
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

    QPushButton* getPasteButton();
    QPushButton* getCutButton();
    QPushButton* getCopyButton();

    QPushButton* getTextFieldButton();

private slots:

private:
    Ui::EditorTools *ui;
};

#endif // EDITORTOOLS_H
