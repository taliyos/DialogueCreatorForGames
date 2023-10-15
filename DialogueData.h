#ifndef DIALOGUEDATA_H
#define DIALOGUEDATA_H

#include <utility>
#include <string>
#include <map>
#include <list>
using namespace std;

/// <summary>A class that holds the raw data for text fields.</summary>
class DialogueData
{

public:
    // constructors
    explicit DialogueData();
    // accessors
    const string getText();
    // setters
    void setText(string newText);
    // Field effect functions
    bool hasFieldEffect(string tag);
    void applyFieldEffect(string tag);
    void removeFieldEffect(string tag);
    void addOrRemoveFieldEffect(string tag);
    // Text effect functions
    bool hasTextEffect(unsigned int index1, unsigned int index2, string tag);
    void applyTextEffect(unsigned int index1, unsigned int index2, string tag);
    void removeTextEffect(unsigned int index1, unsigned int index2, string tag);
    void addOrRemoveTextEffect(unsigned int index1, unsigned int index2, string tag);

private:
    // the raw text
    string text;
    // maps substrings of text to text effect tags
    map<pair<int, int>, list<string>> textToEffects;
    // list of field effects applied to text
    list<string> fieldEffects;
};

#endif // DIALOGUEDATA_H
