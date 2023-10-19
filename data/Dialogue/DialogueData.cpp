#include "DialogueData.h"
#include <algorithm>

// Make sure files are in the correct folders so that we don't make a mess
/// <summary>A class that holds the raw data for text fields.</summary>
DialogueData::DialogueData()
{
    this->text = new string("");
    this->textToEffects = new map<pair<int, int>, list<int>>();
    this->fieldEffects = new list<int>();
}
DialogueData::~DialogueData()
{
    delete this->text;
    delete this-> textToEffects;
    delete this->fieldEffects;
}

void DialogueData::setText(string newText)
{
    *(text) = newText;
}

const string DialogueData::getText()
{
    return *(text);
}

bool DialogueData::hasFieldEffect(int tag)
{
    return find(fieldEffects->begin(), fieldEffects->end(), tag) != fieldEffects->end();
}
void DialogueData::applyFieldEffect(int tag)
{
    fieldEffects->push_back(tag);
}
void DialogueData::removeFieldEffect(int tag)
{
    fieldEffects->remove(tag);
}
void DialogueData::addOrRemoveFieldEffect(int tag)
{
    if (hasFieldEffect(tag))
        removeFieldEffect(tag);
    else
        applyFieldEffect(tag);
}


/// <summary> Looks to see if a given range between index1 and index2 has a text effect with a given tag</summary>
// TODO: FINISH THIS ****
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
    return false;
    */
}
void DialogueData::applyTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    /*
    list<int> * effects = &((*textToEffects)[*(new pair<int, int>(index1, index2))]);
    effects->push_back(tag);
    */
}
void DialogueData::removeTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    /*
    list<int> * effects = &((*textToEffects)[*(new pair<int, int>(index1, index2))]);
    effects->remove(tag);
    */
}
void DialogueData::addOrRemoveTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    /*
    if (hasTextEffect(index1, index2, tag))
        removeTextEffect(index1, index2, tag);
    else
        applyTextEffect(index1, index2, tag);
    */
}
