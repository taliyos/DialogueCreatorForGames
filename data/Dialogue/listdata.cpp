#include "listdata.h"
#include <iterator>

ListData::ListData()
{

}

ListData::ListData(string text)
{

}

ListData::~ListData()
{
    // TODO: FINISH THIS ***
}

void ListData::updateText()
{
    // clear the text
    setText("");
    // add all the elements to the text
    list<string>::iterator itr = (*elements).begin();
    for(itr = elements->begin(); itr != elements->end(); itr++)
    {
        (*text) = (*text) + (*itr);
    }
}
void ListData::updateElements()
{

}

const list<string> ListData::getElements()
{
    return (*elements);
}

void ListData::push_back(string s)
{
    // add the new element
    elements->push_back(s);
    // add to the text
    *(text) = *(text) + s;
}
void ListData::push_font(string s)
{
    // add the new element
    elements->push_front(s);
    // add to the text
    *(text) = s + *(text);
}
void ListData::replace(string s, int index)
{
    // replace the element
    list<string>::iterator itr = (*elements).begin();
    for(int i=0; i <= index; i++){
        ++itr;
    }
    (*itr) = s;
}
void ListData::insert(string s, int index)
{
    // insert the element
    list<string>::iterator itr = (*elements).begin();
    for(int i=0; i < index; i++){
        ++itr;
    }
    elements->insert(itr, s);
}
void ListData::erase(int index)
{
    // remove the element
    list<string>::iterator itr = (*elements).begin();
    for(int i=0; i < index; i++){
        ++itr;
    }
    elements->erase(itr);
}
void ListData::clear()
{
    elements->clear();
    text->clear();
}
