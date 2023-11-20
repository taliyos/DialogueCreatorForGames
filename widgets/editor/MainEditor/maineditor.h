#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include "widgets/editor/Designer/designer.h"
#include "widgets/editor/EditorTools/editortools.h"
#include "data/Fields/fielddata.h"
#include "widgets/tabs/TabableWidget/tabablewidget.h"

namespace Ui {
class MainEditor;
}

class MainEditor : public TabableWidget
{
    Q_OBJECT

public:
    explicit MainEditor(QWidget *parent = nullptr);
    ~MainEditor();

    void preset_createTextField();
    void preset_createTextFieldAndCharacter();
    void preset_createListField();
    void preset_createUserPromptField();
    void preset_createUserListField();

    void loadFile(const QString& filePath);

    // Overrides

    bool MainEditor::save() override;
    bool MainEditor::saveAs() override;
    bool MainEditor::importJSON(QString path = "") override;
    bool MainEditor::importText() override;
    bool MainEditor::importDocx() override;

    bool MainEditor::exportFile() override;

    bool MainEditor::importPreset() override;
    bool MainEditor::exportPreset(int num) override;

    const QString MainEditor::getFilePath() override;

public slots:
    // Field Effects

    /**
     * Applies wobble effect to a selected text field
     */
    void on_actionWobble_triggered();
    /**
     * Applies enlarge effect to a selected text field
     */
    void on_actionEnlarge_triggered();
    /**
     * Applies speedup effect to a selected text field
     */
    void on_actionSpeedup_triggered();
    /**
     * Applies bold effect to a selected text field
     */
    void on_actionBold_triggered();
    /**
     * Applies typed effect to a selected text field
     */
    void on_actionTyped_triggered();
    /**
     * Removes effects from a selected text field
     */
    void on_actionRemoveFieldEffect_triggered();

    // Text Effects

    /**
     * Applies wobble effect to selected text
     */
    void on_actionWobbleText_triggered();
    /**
     * Applies enlarge effect to selected text
     */
    void on_actionEnlargeText_triggered();
    /**
     * Applies speedup effect to selected text
     */
    void on_actionSpeedupText_triggered();
    /**
     * Applies bold effect to selected text
     */
    void on_actionBoldText_triggered();
    /**
     * Applies typed effect to selected text
     */
    void on_actionTypedText_triggered();
    /**
     * Applies a given text effect to a selection of text
     * @param tag: the integer representing the effect
     */
    void applyTextEffect(int tag);
    /**
     * Removes any text effects from a selection of text
     */
    void on_actionRemoveEffect_triggered();

private slots:

    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    

    void createPreset();
    void applyPreset(Preset* preset);

    void ExportToHTML();
    void updateExportButtonVisibility();

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
    QString currentHTML;

    EditorTools* editorTools = nullptr;
    Designer* designer = nullptr;

    FieldData* data = nullptr;
    FieldData* lastActive = nullptr;
};

#endif // MAINEDITOR_H
