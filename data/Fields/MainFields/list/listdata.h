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
/// Aside from the text string, it has a list of indices that are the beginning of each option.
/// </summary>

/**
 * ListData extends MainFieldData, abstracting the text as a list of indecies seperated by delimiters.
 */
class ListData : public MainFieldData
{
public:
    // constructors
    /**
     * Constructs a new InputData
     * @param ui: The QWidget this data is for.
     * @param fromConnection: The connection prior to this element.
     * @param toConnection: The connection following this element.
     * @param options: The list of options to create the text and indicies from.
     */
    ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, list<string> options);
    /**
     * Constructs a new InputData
     * @param ui: The QWidget this data is for.
     * @param fromConnection: The connection prior to this element.
     * @param toConnection: The connection following this element.
     * @param txt: The text to populate with.
     * @param indecies: The indices to set.
     */
    ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, string txt, list<int> indecies);
    /**
     * Constructs a new InputData
     * @param ui: The QWidget this data is for.
     * @param fromConnection: The connection prior to this element.
     * @param toConnection: The connection following this element.
     */
    ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);

    void setIndex(int value);
    int getIndex();

    // list methods
    /**
     * Adds an option to the back of the text, adds an index
     * @param s: the string to push back
     */
    void push_back(string s);
    /**
     * Adds an option to the front of the text, adds an index
     * @param s: the string to push back
     */
    void push_front(string s);
    /**
     * pops the back option of the text, adds an index
     */
    void pop_back();
    /**
     * pops the first option of the text, adds an index
     */
    void pop_front();
    /**
     * Inserts option s at index i.
     * @param i: the index to insert at
     * @param s: the string to insert
     */
    void insert (int i, string s);
    /**
     * Erases the option at index i
     * @param i: the index to erase
     */
    void erase(int i);
    /**
     * Replaces the option at index i with string s
     * @param i: the index to replace at
     * @param s: the string replacement
     */
    void replace(int i, string s);
    /**
     * Sets the text string and index list based on a list of strings
     * @param options the list of options to derive the text and indices from.
     */
    void setTextFromList(list<string> options);
    /**
     * Gets the list of options.
     * @return a list of strings, each being an option
     */
    list<string> toList();
    /**
     * Gets the list of indices
     * @return a list of ints, each being an index of an option.
     */
    list<int> getIndecies();
    /**
     * Prints the options to the qDebug
     */
    void print();
private:
    // the index of this field
    int index = 0;
    // <startLocation>
    list<int> indecies = list<int>();
    ListSettings* settings;
};

#endif // LISTDATA_H
