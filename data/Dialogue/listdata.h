#ifndef LISTDATA_H
#define LISTDATA_H

#include <utility>
#include <string>
#include <list>
#include "fielddata.h"

using namespace std;

/// <summary>
/// This class extends MainFieldData by abstracting its text as a list.
/// The class has a delimiter it uses to mark each index.
/// It also has a list of indecies, pairs of the starting location and length of the index
/// </summary>

class ListData : protected FieldData
{
public:
    // constructors
    ListData();
    ListData(string txt, string delim);
    // setters
    void setDelimiter (string delim);
    void setText (string txt);
    // modifiers
    void push_back(string s);
    void push_front(string s);
    void pop_back(string s);
    void pop_front(string s);
    void insert (int i, string s);
    void erase(int i);
    void replace(int i, string s);
    list<string> toList();
    list<pair<int,int>> getIndecies();
private:
    string delimiter;
    // <startLocation, length>
    list<pair<int, int>> indecies;
    // parses the indecies
    void generateIndecies();
    // the base delimeter if one isn't set
    //static const string baseDelimiter = "***";
};

#endif // LISTDATA_H
