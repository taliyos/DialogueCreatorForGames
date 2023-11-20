#include "preset.h"
#include "data/Fields/fielddata.h"
#include "data/ConnectionData/connectiondata.h"
#include "widgets/editor/MainEditor/maineditor.h"

Preset::Preset(FieldData* data)
{
    Preset::createPreset(data);
}

Preset::Preset(std::vector<FieldTypes> fieldTypes)
{
    int totalText = 0;
    int totalCharacter =0;
    int totalList = 0;
    int totalUserPrompt = 0;
    int totalUserList = 0;
    for (std::vector<FieldTypes>::iterator itr = fieldTypes.begin(); itr != fieldTypes.end(); itr++)
    {
        storage.push_back(*itr);
        switch (*itr) {
        case Text:
            totalText++;
            break;
        case TextCharacter:
            totalCharacter++;
            break;
        case List:
            totalList++;
            break;
        case UserPrompt:
            totalUserPrompt++;
            break;
        case UserList:
            totalUserList++;
            break;
        }
    }

    std::string desc = "";
    if (totalText != 0) desc += "Text: "+ std::to_string(totalText) + ", ";
    if (totalCharacter != 0) desc += "Character: " + std::to_string(totalCharacter) + ", ";
    if (totalList != 0) desc += "List: " + std::to_string(totalList) + ", ";
    if (totalUserPrompt != 0) desc += "User Prompt: " + std::to_string(totalUserPrompt) + ", ";
    if (totalUserList != 0) desc += "User List: " + std::to_string(totalUserList) + ", ";

    desc = desc.substr(0, desc.size() - 2);

    description = QString::fromStdString(desc);
}

void Preset::createPreset(FieldData* data) {
    FieldData* curr = data;
    int totalText = 0;
    int totalCharacter =0;
    int totalList = 0;
    int totalUserPrompt = 0;
    int totalUserList = 0;
    while (curr != nullptr) {
        storage.push_back(curr->getFieldType());

        switch (curr->getFieldType()) {
        case Text:
            totalText++;
            break;
        case TextCharacter:
            totalCharacter++;
            break;
        case List:
            totalList++;
            break;
        case UserPrompt:
            totalUserPrompt++;
            break;
        case UserList:
            totalUserList++;
            break;
        }

        if (!curr->getToConnection()) break;
        curr = curr->getToConnection()->getNext();
    }

    std::string desc = "";
    if (totalText != 0) desc += "Text: "+ std::to_string(totalText) + ", ";
    if (totalCharacter != 0) desc += "Character: " + std::to_string(totalCharacter) + ", ";
    if (totalList != 0) desc += "List: " + std::to_string(totalList) + ", ";
    if (totalUserPrompt != 0) desc += "User Prompt: " + std::to_string(totalUserPrompt) + ", ";
    if (totalUserList != 0) desc += "User List: " + std::to_string(totalUserList) + ", ";

    desc = desc.substr(0, desc.size() - 2);

    description = QString::fromStdString(desc);

}

// MAIN EDITOR SHOULD NOT BE INCLUDED. THIS IS TEMPORARY.
void Preset::apply(FieldData* data, MainEditor* editor) {
    FieldData* curr = data;
    while (curr != nullptr && curr->getToConnection() != nullptr) {
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

QString Preset::getDescription() const {
    return description;
}

std::vector<FieldTypes> Preset::getStorage() const
{
    return storage;
}
