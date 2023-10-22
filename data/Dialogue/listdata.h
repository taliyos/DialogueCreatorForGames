#ifndef LISTDATA_H
#define LISTDATA_H

#include <utility>
#include <string>
#include <list>
#include "fielddata.h"

using namespace std;

/// <summary>
/// This class extends MainFieldData by abstracting the text as a list of options.
/// </summary>

class ListData : protected FieldData
{
public:
    // constructors
    ListData();
    ListData(string s);
    // deconstructor
    ~ListData();
    // Accessors
    const list<string> getElements();
    // Setters
    void push_back(string s);
    void push_font(string s);
    void replace(string s, int index);
    void insert(string s, int index);
    void erase(int index);
    void clear();
private:
    list<string>* elements;
    void updateText();
    void updateElements();
};

#endif // LISTDATA_H
