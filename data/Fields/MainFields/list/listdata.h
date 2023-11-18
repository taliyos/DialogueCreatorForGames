#ifndef LISTDATA_H
#define LISTDATA_H

#include <QWidget>
#include <utility>
#include <string>
#include <list>
#include <widgets/editor/EditorTools/Settings/listsettings.h>
#include "../mainfielddata.h"

using namespace std;

/// <summary>
/// This class extends MainFieldData by abstracting its text as a list.
/// The class has a delimiter it uses to mark each index.
/// It also has a list of indecies, pairs of the starting location and length of the index
/// </summary>

/**
 * ListData extends MainFieldData, abstracting the text as a list of indecies seperated by delimiters.
 */
class ListData : public MainFieldData
{
public:
    // constructors
    ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, list<string> options);
    /**
     * @brief ListData
     * @param ui
     * @param fromConnection
     * @param toConnection
     * @param txt
     * @param delim
     */
    ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, string txt, list<int> indecies);
    /**
     * @brief ListData
     * @param ui
     * @param fromConnection
     * @param toConnection
     */
    ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
    void setIndex(int value);
    int getIndex();
    // modifiers
    //
    void push_back(string s);
    //
    void push_front(string s);
    //
    void pop_back();
    //
    void pop_front();
    //
    void insert (int i, string s);
    //
    void erase(int i);
    //
    void replace(int i, string s);
    //
    void setTextFromList(list<string> options);
    //
    list<string> toList();
    //
    list<int> getIndecies();
    //
    void print();
private:
    // the index of this field
    int index = 0;
    // <startLocation>
    list<int> indecies = list<int>();
    ListSettings* settings;
};

#endif // LISTDATA_H
