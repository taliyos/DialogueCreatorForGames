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

    void preset_createTextField();
    void preset_createTextFieldAndCharacter();
    void preset_createListField();
    void preset_createUserPromptField();
    void preset_createUserListField();

private slots:
    // File -> Open
    // Opens a project file into the application (.json)
    void on_actionOpen_triggered();
    // File -> Save
    // Identical to exportJson, except it uses the currentFile (current filename)
    void on_actionSave_triggered();
    // File -> Save As
    // Identical to exportJson except it sets currentFile
    void on_actionSaveAs_triggered();
    // File -> Import -> .txt
    // Imports a .txt file, creating new text fields for each paragraph
    void on_actionImportTxt_triggered();
    // File -> Import -> .docx
    // Imports a .docx file, creating new text fields for each paragraph
    void on_actionImportDocx_triggered();
    // File -> Import -> .json
    // Imports a .json file, creating new text fields for each paragraph
    // Also create FieldData objects, populated with text, field effects, and text effects
    void on_actionImportJson_triggered();
    // File -> Export -> .json
    // Converts data (list of FieldData objects) into a json file
    void on_actionExportJson_triggered();
    // Closes the program
    void on_actionExit_triggered();

    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void on_actionNew_triggered();

    // Field Effects

    // Applies wobble effect to a selected text field
    void on_actionWobble_triggered();
    // Applies enlarge effect to a selected text field
    void on_actionEnlarge_triggered();
    // Applies speedup effect to a selected text field
    void on_actionSpeedup_triggered();
    // Applies bold effect to a selected text field
    void on_actionBold_triggered();
    // Applies typed effect to a selected text field
    void on_actionTyped_triggered();
    // Removes effects from a selected text field
    void on_actionRemoveFieldEffect_triggered();

    // Text Effects
    // Applies wobble effect to selected text
    void on_actionWobbleText_triggered();
    // Applies enlarge effect to selected text
    void on_actionEnlargeText_triggered();
    // Applies speedup effect to selected text
    void on_actionSpeedupText_triggered();
    // Applies bold effect to selected text
    void on_actionBoldText_triggered();
    // Applies typed effect to selected text
    void on_actionTypedText_triggered();
    /**
     * Applies a given text effect to a selection of text
     * @param tag: the integer representing the effect
     */
    void applyTextEffect(int tag);
    // Removes any text effects from a selection of text
    void on_actionRemoveEffect_triggered();

    void createPreset();
    void applyPreset(Preset* preset);
    // Imports a preset from a .preset file
    void on_actionImportPreset_2_triggered();
    // Exports preset 1 to a .preset file
    void on_actionExportPreset1_triggered();
    // Exports preset 2 to a .preset file
    void on_actionExportPreset2_triggered();
    // Exports preset 3 to a .preset file
    void on_actionExportPreset3_triggered();
    // Exports preset 4 to a .preset file
    void on_actionExportPreset4_triggered();
    /**
     * Exports a given preset to a .preset file
     * @param num: the preset to be exported
     */
    void exportPreset(int num);
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
     * 
     * @param field - The ui field to remove
    */
    void removeField(TextField* field);
    void removeListField(ListField* field);

    /**
     * @brief updateListFields
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

    QString currentFile;
};

#endif // MAINEDITOR_H
