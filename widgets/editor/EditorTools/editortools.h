#ifndef EDITORTOOLS_H
#define EDITORTOOLS_H

#include <QPushButton>
#include "widgets/editor/Settings/settings.h"
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

    // Clipboard
    QPushButton* getPaste();
    QPushButton* getCut();
    QPushButton* getCopy();

    // Fields
    QPushButton* getTextField();
    QPushButton* getCustomField1();
    QPushButton* getCustomField2();
    QPushButton* getCustomField3();
    QPushButton* getCustomField4();
    QPushButton* getCustomField5();
    QPushButton* getCustomField6();
    QPushButton* getFieldSettings();

    // Effects
    QPushButton* getDisplayEffect();
    QPushButton* getDisplayEffectFavorite1();
    QPushButton* getDisplayEffectFavorite2();
    QPushButton* getModifier();
    QPushButton* getModifierFavorite1();
    QPushButton* getModifierFavorite2();
    QPushButton* getCharacter();
    QPushButton* getCharacterFavorite1();
    QPushButton* getCharacterFavorite2();
    QPushButton* getEffectSettings();


    Settings* getSettings();
    // Presets
    QPushButton* getPreset1();
    QPushButton* getPreset2();
    QPushButton* getPreset3();
    QPushButton* getPreset4();
    QPushButton* getAddPreset();
    QPushButton* getMorePresets();
    QPushButton* getPresetSettings();

private slots:

private:
    Ui::EditorTools *ui;
};

#endif // EDITORTOOLS_H
