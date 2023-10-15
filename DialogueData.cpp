#include "DialogueData.h"
#include <algorithm>

/// <summary>A class that holds the raw data for text fields.</summary>
DialogueData::DialogueData()
{
    this->text = "";
    this->textToEffects = *(new map<pair<int, int>, list<string>>());
    this->fieldEffects = *(new list<string>());
}

void DialogueData::setText(string newText)
{
    text = newText;
}

const string DialogueData::getText()
{
    return text;
}

bool DialogueData::hasFieldEffect(string tag)
{
    return find(fieldEffects.begin(), fieldEffects.end(), tag) != fieldEffects.end();
}
void DialogueData::applyFieldEffect(string tag)
{
    fieldEffects.push_back(tag);
}
void DialogueData::removeFieldEffect(string tag)
{
    fieldEffects.remove(tag);
}
void DialogueData::addOrRemoveFieldEffect(string tag)
{
    if (hasFieldEffect(tag))
        removeFieldEffect(tag);
    else
        applyFieldEffect(tag);
}

/// <summary> Looks to see if a given range between index1 and index2 has a text effect with a given tag</summary>
// TODO: FINISH THIS ****
bool DialogueData::hasTextEffect(unsigned int index1, unsigned int index2, string tag)
{
    // Check to see if the range is valid
    if (index1 > index2 || index1 >= text.length() || index2 >= text.length())
        return false;
    // Look for a mapping of the text fields that covers this range
    for(map<pair<int,int>,list<string>>::iterator it = textToEffects.begin(); it != textToEffects.end(); it++)
    {
        // Check to see if this range contains the effect
        if (it->first.first <= index1 && it->first.second <= index2)
            return find(it->second.begin(), it->second.end(), tag) != it->second.end();
    }
    // Return false if it isn't found
    return false;
}
void DialogueData::applyTextEffect(unsigned int index1, unsigned int index2, string tag)
{
    list<string> * effects = &(textToEffects[*(new pair<int, int>(index1, index2))]);
    effects->push_back(tag);
}
void DialogueData::removeTextEffect(unsigned int index1, unsigned int index2, string tag)
{
    list<string> * effects = &(textToEffects[*(new pair<int, int>(index1, index2))]);
    effects->remove(tag);
}
void DialogueData::addOrRemoveTextEffect(unsigned int index1, unsigned int index2, string tag)
{
    if (hasTextEffect(index1, index2, tag))
        removeTextEffect(index1, index2, tag);
    else
        applyTextEffect(index1, index2, tag);
}
