#include "editortools.h"
#include "ui_editortools.h"

EditorTools::EditorTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorTools)
{
    ui->setupUi(this);

    displayDropdown = new EffectsDropdown();
    characterDropdown = new EffectsDropdown();
    modifierDropdown = new EffectsDropdown();

    displayDropdown->setName(QString::fromStdString("Display Effects"));
    characterDropdown->setName(QString::fromStdString("Character Effects"));
    modifierDropdown->setName(QString::fromStdString("Modifers"));

    connect(ui->displayEffect, &QAbstractButton::clicked, this, &EditorTools::showDisplayDropdown);
    connect(ui->character, &QAbstractButton::clicked, this, &EditorTools::showCharacterDropdown);
    connect(ui->modifier, &QAbstractButton::clicked, this, &EditorTools::showModifierDropdown);
}

EditorTools::~EditorTools()
{
    delete displayDropdown;
    delete characterDropdown;
    delete modifierDropdown;

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

// Dropdowns
EffectsDropdown* EditorTools::getDisplayDropdown() const { return displayDropdown; }
EffectsDropdown* EditorTools::getCharacterDropdown() const { return characterDropdown; }
EffectsDropdown* EditorTools::getModifierDropdown() const { return modifierDropdown; }

void EditorTools::populateDisplayEffects(EffectsVector effects) { populateEffects(displayDropdown, effects); }
void EditorTools::populateCharacterEffects(EffectsVector effects) { populateEffects(characterDropdown, effects); }
void EditorTools::populateModifierEffects(EffectsVector effects) { populateEffects(modifierDropdown, effects); }

void EditorTools::populateEffects(EffectsDropdown* dropdown, EffectsVector effects) {
    if (effects.size() <= 0) return;

    // Adds each effect to the specified dropdown
    for (EffectsVector::iterator itr = effects.begin(); itr != effects.end(); itr++) {
        QPushButton* button = dropdown->createButton(QString::fromStdString(itr->first));
        QObject::connect(button, &QAbstractButton::clicked, itr->second);
    }
}

// Effects Dropdowns
void EditorTools::showDropdown(EffectsDropdown* dropdown, QPoint point) {
    // Finds the bottom center point of the parent button to make the dropdown appear at.
    point.setX(point.x() - 32);
    point.setY(point.y() + ui->character->height());
    dropdown->popup(point);
}

void EditorTools::showDisplayDropdown() {showDropdown(displayDropdown, ui->displayEffect->mapToGlobal(ui->displayEffect->pos())); }
void EditorTools::showCharacterDropdown() { showDropdown(characterDropdown, ui->displayEffect->mapToGlobal(ui->character->pos())); }
void EditorTools::showModifierDropdown() { showDropdown(modifierDropdown, ui->displayEffect->mapToGlobal(ui->modifier->pos())); }
