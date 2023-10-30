#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include "widgets/editor/Designer/designer.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "data/ConnectionData/connectiondata.h"
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
    void handlePreviewRequest(const QString& content);
    void createTextField();

private:
    Ui::MainEditor *ui;

    EditorTools* editorTools;
    Designer* designer;

    ConnectionData* connectionData;

    QString currentFile;
};

#endif // MAINEDITOR_H
