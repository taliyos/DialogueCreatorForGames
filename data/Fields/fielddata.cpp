#include <QWidget>
#include <algorithm>

#include "fielddata.h"
#include "../ConnectionData/connectionData.h"
#include "widgets/editor/Fields/CharacterField/characterfield.h"
#include "widgets/editor/Fields/TextField/textfield.h"


/// <summary>A class that holds the raw data for text fields.</summary>
FieldData::FieldData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection)
{
    this->ui = ui;
    this->fromConnection = fromConnection;
    this->toConnection = toConnection;

    this->text = string("");
    this->textToEffects = map<pair<int, int>, list<int>>();
    this->fieldEffects = list<int>();
}

FieldData::~FieldData() {
    // Delete the UI Widget before removing the data
    if (ui != nullptr) {
        delete ui;
    }
}

void FieldData::setFieldType(FieldTypes type) {
    qInfo("set field type to: " + type);
    fieldType = type;
}

FieldTypes FieldData::getFieldType() const { return fieldType; }


void FieldData::setText(string newText)
{
    text = newText;
}
const string FieldData::getText()
{
    return text;
}
const map<pair<int, int>, list<int>> FieldData::getTextEffects()
{
    return this->textToEffects;
}
const list<int> FieldData::getFieldEffects()
{
    return this->fieldEffects;
}
bool FieldData::hasFieldEffect(int tag)
{
    return find(fieldEffects.begin(), fieldEffects.end(), tag) != fieldEffects.end();
}
void FieldData::applyFieldEffect(int tag)
{
    fieldEffects.push_back(tag);
}
void FieldData::removeFieldEffect(int tag)
{
    fieldEffects.remove(tag);
}
void FieldData::addOrRemoveFieldEffect(int tag)
{
    if (hasFieldEffect(tag))
        removeFieldEffect(tag);
    else
    {
        // Since only one field effect can be active, remove the previous effects here
        fieldEffects = list<int>();
        applyFieldEffect(tag);
    }
}

// TODO: FINISH THIS ****
/// <summary>
/// Looks to see if a given range between index1 and index2 has a text effect with a given tag
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     none
/// returns:
///     if the given range has the text effect applied somewhere within
/// </summary>
bool FieldData::hasTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    qDebug() << "test";

    // Check to see if the range is valid
    if (index1 >= index2) //|| index1 >= text.length()|| index2 >= text.length())
        return false;
    qDebug() << "test2";
    // Look for a mapping of the text fields that covers this range
    for(map<pair<int,int>,list<int>>::iterator it = textToEffects.begin(); it != textToEffects.end(); it++)
    {
        // Check to see if this range contains the effect
//        if (it->first.first <= index1 && it->first.second <= index2)
//            return find(it->second.begin(), it->second.end(), tag) != it->second.end();

        // Check to see if this range contains ANY effect. If so, return true
        qDebug() << "in loop";
        qDebug() << index1 << index2 << it->first.first << it->first.second;
        if ((index1 >= it->first.first && index1 < it->first.second) || (index2 >= it->first.first && index2 < it->first.second) )
            return true;
    }
    // Return false if it isn't found

    return false;
}

/// <summary>
/// applies a text effect to the given substring in the text.
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     textToEffects
/// returns:
///     none
/// </summary>
void FieldData::applyTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    // remember: map<pair<int, int>, list<int>>*
    pair<int, int> key = pair<int, int>(index1, index2);
    textToEffects[key] = {tag};
}

/// <summary>
/// removes a text effect from the given substring in the text
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     textToEffects
/// returns:
///     none
/// </summary>
void FieldData::removeTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    // remember: map<pair<int, int>, list<int>>*
    pair<int, int> key = pair<int, int>(index1, index2);
    textToEffects.erase(key);
}

/// <summary>
/// applies the given text effect to a substring if it is not applied within.
/// otherwise, removes the effect.
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     textToEffects
/// returns:
///     none
/// </summary>
void FieldData::addOrRemoveTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    if (hasTextEffect(index1, index2, tag))
        removeTextEffect(index1, index2, tag);
    else
        applyTextEffect(index1, index2, tag);
}

const ConnectionData* FieldData::replaceFromConnection(ConnectionData* connection) {
    fromConnection = connection;
    return nullptr;
}

const ConnectionData* FieldData::replaceToConnection(ConnectionData* connection) {
    ConnectionData* previous = toConnection;
    toConnection = connection;
    return previous;
}

ConnectionData* FieldData::getToConnection() {
    return toConnection;
}

ConnectionData* FieldData::getFromConnection() {
    return fromConnection;
}

QWidget* FieldData::getUi() {
    return ui;
}

void FieldData::removeAll() {
    if (toConnection != nullptr) {
        toConnection->removeAll();
    }

    delete this;
}

const nlohmann::json FieldData::toJson()
{
    nlohmann::json j;
    j["text"] = this->text;
    j["fieldEffects"] = this->fieldEffects;
    j["textEffects"] = this->textToEffects;
    TextField* field = reinterpret_cast <TextField*>(getUi());
    j["soundFile"] = field->getSoundFile().toStdString();
    CharacterField* characterField = field->getCharacterField();
    j["character"] = "";
    if (characterField)
        j["character"] = characterField->getText().toStdString();

    return j;
}

void FieldData::fromJson(nlohmann::json j)
{
    this->text = j["text"];
    list<int> fieldEffects = j["fieldEffects"];
    this->fieldEffects = fieldEffects;
    this->textToEffects =  j["textEffects"];
    TextField* field = reinterpret_cast <TextField*>(getUi());
    if (QString::fromStdString(j["character"]).isEmpty())
        return;

    CharacterField* characterField = field->getCharacterField();
    if (!characterField)
    {
        field->addCharacterWidget();
        characterField = field->getCharacterField();
    }
    characterField->setText(QString::fromStdString(j["character"]));
}
