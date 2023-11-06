#include "preset.h"
#include "data/Fields/fielddata.h"
#include "data/ConnectionData/connectiondata.h"
#include "widgets/editor/MainEditor/maineditor.h"

Preset::Preset(FieldData* data)
{
    Preset::createPreset(data);
}

void Preset::createPreset(FieldData* data) {
    FieldData* curr = data;
    while (curr != nullptr) {
        storage.push_back(curr->getFieldType());
        curr = curr->getToConnection()->getNext();

        if (!curr->getToConnection()) break;
    }
}

// MAIN EDITOR SHOULD NOT BE INCLUDED. THIS IS TEMPORARY.
void Preset::apply(FieldData* data, MainEditor* editor) {
    FieldData* curr = data;
    while (curr->getToConnection() != nullptr) {
        curr = curr->getToConnection()->getNext();
    }

    for (std::vector<FieldTypes>::iterator itr = storage.begin(); itr != storage.end(); itr++) {
        switch (*itr) {
            case Text:
                editor->preset_createTextField();
                break;
            case TextCharacter:
                editor->preset_createTextFieldAndCharacter();
                break;
            case List:
                editor->preset_createListField();
                break;
            case UserPrompt:
                editor->preset_createUserPromptField();
                break;
            case UserList:
                editor->preset_createUserListField();
                break;
        }
    }
}
