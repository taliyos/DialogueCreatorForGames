#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include "widgets/editor/Designer/designer.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "data/Fields/fielddata.h"
#include <QMainWindow>

namespace Ui {
class MainEditor;
}

class MainEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainEditor(QWidget *parent = nullptr);
    ~MainEditor();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExit_triggered();

    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void on_actionNew_triggered();

    void createTextField();
    void removeHead();
    void removeField(TextField* field);

private:
    Ui::MainEditor *ui = nullptr;

    EditorTools* editorTools = nullptr;
    Designer* designer = nullptr;

    FieldData* data = nullptr;

    QString currentFile;
};

#endif // MAINEDITOR_H
