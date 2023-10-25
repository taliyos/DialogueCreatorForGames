#ifndef DIALOGUEDATA_H
#define DIALOGUEDATA_H

#include <utility>
#include <string>
#include <map>
#include <list>
#include <json.hpp>
using namespace std;

/// <summary>A class that holds the raw data for text fields.</summary>
class DialogueData
{

public:
    // constructors
    DialogueData();
    // deconstructor
    ~DialogueData();
    // accessors
    const string getText();
    // setters
    void setText(string newText);
    // Field effect functions
    const list<int> getFieldEffects();
    bool hasFieldEffect(int tag);
    void applyFieldEffect(int tag);
    void removeFieldEffect(int tag);
    void addOrRemoveFieldEffect(int tag);
    // Text effect functions
    const map<pair<int, int>, list<int>> getTextEffects();
    bool hasTextEffect(unsigned int index1, unsigned int index2, int tag);
    void applyTextEffect(unsigned int index1, unsigned int index2, int tag);
    void removeTextEffect(unsigned int index1, unsigned int index2, int tag);
    void addOrRemoveTextEffect(unsigned int index1, unsigned int index2, int tag);
    // Json
    const nlohmann::json toJson();
    void fromJson(nlohmann::json j);

private:
    // the raw text
    string text;
    // maps substrings of text to text effect tags
    map<pair<int, int>, list<int>> textToEffects;
    // list of field effects applied to text
    list<int> fieldEffects;
};

#endif // DIALOGUEDATA_H
