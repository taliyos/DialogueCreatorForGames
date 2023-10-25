#include "DialogueData.h"
#include <algorithm>

/// <summary>A class that holds the raw data for text fields.</summary>
DialogueData::DialogueData()
{
    this->text = "";
    this->textToEffects = map<pair<int, int>, list<int>>();
    this->fieldEffects = list<int>();
}
DialogueData::~DialogueData()
{
//    delete this->text;
//    delete this-> textToEffects;
//    delete this->fieldEffects;
}

void DialogueData::setText(string newText)
{
    this->text = newText;
}
const string DialogueData::getText()
{
    return this->text;
}
const map<pair<int, int>, list<int>> DialogueData::getTextEffects()
{
    return this->textToEffects;
}
const list<int> DialogueData::getFieldEffects()
{
    return this->fieldEffects;
}
bool DialogueData::hasFieldEffect(int tag)
{
    return find(fieldEffects.begin(), fieldEffects.end(), tag) != fieldEffects.end();
}
void DialogueData::applyFieldEffect(int tag)
{
    this->fieldEffects.push_back(tag);
}
void DialogueData::removeFieldEffect(int tag)
{
    fieldEffects.remove(tag);
}
void DialogueData::addOrRemoveFieldEffect(int tag)
{
    if (hasFieldEffect(tag))
        removeFieldEffect(tag);
    else
        applyFieldEffect(tag);
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
bool DialogueData::hasTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    /*
    // Check to see if the range is valid
    if (index1 > index2 || index1 >= text->length() || index2 >= text->length())
        return false;
    // Look for a mapping of the text fields that covers this range
    for(map<pair<int,int>,list<int>>::iterator it = textToEffects->begin(); it != textToEffects->end(); it++)
    {
        // Check to see if this range contains the effect
        if (it->first.first <= index1 && it->first.second <= index2)
            return find(it->second.begin(), it->second.end(), tag) != it->second.end();
    }
    // Return false if it isn't found
    */
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
void DialogueData::applyTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    // remember: map<pair<int, int>, list<int>>*
    pair<int, int> key = pair<int, int>(index1, index2);
    list<int> * effects = &(textToEffects[key]);
    effects->push_back(tag);
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
void DialogueData::removeTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    // remember: map<pair<int, int>, list<int>>*
    pair<int, int> key = pair<int, int>(index1, index2);
    list<int> * effects = &(textToEffects[key]);
    effects->remove(tag);
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
void DialogueData::addOrRemoveTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    if (hasTextEffect(index1, index2, tag))
        removeTextEffect(index1, index2, tag);
    else
        applyTextEffect(index1, index2, tag);
}

const nlohmann::json DialogueData::toJson()
{
    nlohmann::json j;
    j["text"] = this->text;
    j["fieldEffects"] = this->fieldEffects;
    j["textEffects"] = this->textToEffects;

    return j;
}

void DialogueData::fromJson(nlohmann::json j)
{
    this->text = j["text"];
    list<int> fieldEffects = j["fieldEffects"];
    this->fieldEffects = fieldEffects;
    this->textToEffects = j["textEffects"];
}
