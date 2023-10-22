#ifndef FIELDDATA_H
#define FIELDDATA_H

#include <utility>
#include <string>
#include <map>
#include <list>

class CharacterData;

using namespace std;

/// <summary>A class that holds the raw data for text fields.</summary>
class FieldData
{

public:
    // constructors
    FieldData();
    // deconstructor
    ~FieldData();
    // accessors
    const string getText();
    // setters
    void setText(string newText);
    // Field effect functions
    bool hasFieldEffect(int tag);
    void applyFieldEffect(int tag);
    void removeFieldEffect(int tag);
    void addOrRemoveFieldEffect(int tag);
    // Text effect functions
    bool hasTextEffect(unsigned int index1, unsigned int index2, int tag);
    void applyTextEffect(unsigned int index1, unsigned int index2, int tag);
    void removeTextEffect(unsigned int index1, unsigned int index2, int tag);
    void addOrRemoveTextEffect(unsigned int index1, unsigned int index2, int tag);

protected:
    // the raw text
    string* text;
    // maps substrings of text to text effect tags
    map<pair<int, int>, list<int>>* textToEffects;
    // list of field effects applied to text
    list<int>* fieldEffects;
    // a character box
    CharacterData* character;
};

#endif // FIELDDATA_H
