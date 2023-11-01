#ifndef FIELDDATA_H
#define FIELDDATA_H

#include <utility>
#include <string>
#include <map>
#include <list>
#include "json.hpp"
#include <QWidget>

class ConnectionData;
class CharacterData;

using namespace std;

/// <summary>A class that holds the raw data for text fields.</summary>
class FieldData
{

public:
    // constructors
    FieldData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
    ~FieldData();
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

    /**
     * Replaces the current fromConnection with a new value.
     * 
     * @params connection - the new connection to use
     * @return the old from connection, which was removed.
    */
    const ConnectionData* replaceFromConnection(ConnectionData* connection);
    
    /**
     * Replaces the current toConnection with a new value.
     * 
     * @params connection - the new connection to use
     * @return the old from connection, which was removed.
    */
    const ConnectionData* replaceToConnection(ConnectionData* connection);
    ConnectionData* getFromConnection();
    ConnectionData* getToConnection();

    QWidget* getUi();

    /**
     * Deletes all forward connections (both FieldData and ConnectionData)
    */
    void removeAll();


protected:
    // the raw text
    string text;
    // maps substrings of text to text effect tags
    map<pair<int, int>, list<int>> textToEffects;
    // list of field effects applied to text
    list<int> fieldEffects;

private:

    // Language altered between ConnectionData and FieldData to make
    // the difference when using it clear.
    ConnectionData* fromConnection = nullptr;
    ConnectionData* toConnection = nullptr;

    QWidget* ui;
};

#endif // FIELDDATA_H
