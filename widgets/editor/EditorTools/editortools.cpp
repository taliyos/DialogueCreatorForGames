#include "editortools.h"
#include "ui_editortools.h"

EditorTools::EditorTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorTools)
{
    ui->setupUi(this);
}

EditorTools::~EditorTools()
{
    delete ui;
}

// Clipboard
QPushButton* EditorTools::getPaste() { return ui->paste; }
QPushButton* EditorTools::getCut() { return ui->cut; }
QPushButton* EditorTools::getCopy() { return ui->copy; }

// Fields
QPushButton* EditorTools::getTextField() { return ui->textField; }
QPushButton* EditorTools::getCustomField1() { return ui->customField1; }
QPushButton* EditorTools::getCustomField2() { return ui->customField2; }
QPushButton* EditorTools::getCustomField3() { return ui->customField3; }
QPushButton* EditorTools::getCustomField4() { return ui->customField4; }
QPushButton* EditorTools::getCustomField5() { return ui->customField5; }
QPushButton* EditorTools::getCustomField6() { return ui->customField6; }
QPushButton* EditorTools::getFieldSettings() { return ui->fieldSettings; }

// Effects
QPushButton* EditorTools::getDisplayEffect() { return ui->displayEffect; }
QPushButton* EditorTools::getDisplayEffectFavorite1() { return ui->displayEffectFavorite1; }
QPushButton* EditorTools::getDisplayEffectFavorite2() { return ui->displayEffectFavorite2; }
QPushButton* EditorTools::getModifier() { return ui->modifier; }
QPushButton* EditorTools::getModifierFavorite1() { return ui->modifierFavorite1; }
QPushButton* EditorTools::getModifierFavorite2() { return ui->modifierFavorite2; }
QPushButton* EditorTools::getCharacter() { return ui->character; }
QPushButton* EditorTools::getCharacterFavorite1() { return ui->characterFavorite1; }
QPushButton* EditorTools::getCharacterFavorite2() { return ui->characterFavorite2; }
QPushButton* EditorTools::getEffectSettings() { return ui->effectSettings; }

// Presets
QPushButton* EditorTools::getPreset1() { return ui->preset1; }
QPushButton* EditorTools::getPreset2() { return ui->preset2; }
QPushButton* EditorTools::getPreset3() { return ui->preset3; }
QPushButton* EditorTools::getPreset4() { return ui->preset4; }
QPushButton* EditorTools::getAddPreset() { return ui->addPreset; }
QPushButton* EditorTools::getMorePresets() { return ui->morePresets; }
QPushButton* EditorTools::getPresetSettings() { return ui->presetSettings; }
