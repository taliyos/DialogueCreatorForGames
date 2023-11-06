#ifndef EDITORTOOLS_H
#define EDITORTOOLS_H

#include <QPushButton>
#include <QWidget>
#include "widgets/editor/EditorTools/EffectsDropdown/effectsdropdown.h"

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

    // Presets
    QPushButton* getPreset1();
    QPushButton* getPreset2();
    QPushButton* getPreset3();
    QPushButton* getPreset4();
    QPushButton* getAddPreset();
    QPushButton* getMorePresets();
    QPushButton* getPresetSettings();

    // Dropdowns
    EffectsDropdown* getDisplayDropdown() const;
    EffectsDropdown* getCharacterDropdown() const;
    EffectsDropdown* getModifierDropdown() const;

    typedef std::function<void ()> EffectFunc;
    typedef std::pair<std::string, EffectFunc> EffectPair;
    typedef std::vector<EffectPair> EffectsVector;

    void populateDisplayEffects(EffectsVector effects);
    void populateCharacterEffects(EffectsVector effects);
    void populateModifierEffects(EffectsVector effects);

signals:
    void characterEffectRequested(int effectNumber);


private slots:

private:
    Ui::EditorTools *ui;

    EffectsDropdown* displayDropdown;
    EffectsDropdown* characterDropdown;
    EffectsDropdown* modifierDropdown;

    void populateEffects(EffectsDropdown* dropdown, EffectsVector effects);

    void showDropdown(EffectsDropdown* dropdown, const QPoint point);

    void showDisplayDropdown();
    void showCharacterDropdown();
    void showModifierDropdown();
};

#endif // EDITORTOOLS_H
