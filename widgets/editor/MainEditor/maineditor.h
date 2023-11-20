#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include "widgets/editor/Designer/designer.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "data/Fields/fielddata.h"
#include "widgets/tabs/TabableWidget/tabablewidget.h"
#include <QMainWindow>

namespace Ui {
class MainEditor;
}

class MainEditor : public TabableWidget
{
    Q_OBJECT

public:
    explicit MainEditor(QWidget *parent = nullptr);
    ~MainEditor();

    void applyTextEffect(int tag);

    void preset_createTextField();
    void preset_createTextFieldAndCharacter();
    void preset_createListField();
    void preset_createUserPromptField();
    void preset_createUserListField();

    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    // Overrides

    bool MainEditor::save() override;
    bool MainEditor::saveAs() override;

    

public slots:
    // Field Effects
    void on_actionWobble_triggered();
    void on_actionEnlarge_triggered();
    void on_actionSpeedup_triggered();
    void on_actionBold_triggered();
    void on_actionTyped_triggered();
    void on_actionRemoveFieldEffect_triggered();

    // Text Effects
    void on_actionWobbleText_triggered();
    void on_actionEnlargeText_triggered();
    void on_actionSpeedupText_triggered();
    void on_actionBoldText_triggered();
    void on_actionTypedText_triggered();
    void on_actionRemoveEffect_triggered();

private slots:

    void createPreset();
    void applyPreset(Preset* preset);

    /**
     * Creates a text field and adds it to the UI
    */
    void handlePreviewRequest(const QString& content, const QString& content2, FieldData* textData);
    void createTextField();
    void createListField();

    /**
     * Removes the head of the data (field container)
    */
    void removeHead();

    /**
     * Removes the specified field from the data and UI
     * @param field - The ui field to remove
    */
    void removeField(TextField* field);
    void removeListField(ListField* field);

    /**
     * Updates the entries available in the list fields
     * @param options
     */
    void updateListFields(string txt);

    FieldData* getActiveField();

private:
    Ui::MainEditor *ui = nullptr;

    EditorTools* editorTools = nullptr;
    Designer* designer = nullptr;

    FieldData* data = nullptr;
    FieldData* lastActive = nullptr;
};

#endif // MAINEDITOR_H
