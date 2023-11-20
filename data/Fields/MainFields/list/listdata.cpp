#include <QWidget>
#include "listdata.h"
#include <iterator>
#include <qDebug>

#include "../mainfielddata.h"
#include "widgets/editor/Fields/ListField/listfield.h"

ListData::ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection) : MainFieldData(ui, fromConnection, toConnection)
{
    ListField* field = reinterpret_cast <ListField*>(ui);
    field->setData(this);

    this->text = "";
    this->indecies = list<int>();

    setFieldType(List);
}

ListData::ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, string txt, list<int> indecies) : MainFieldData(ui, fromConnection, toConnection)
{
    ListField* field = reinterpret_cast <ListField*>(ui);
    field->setData(this);

    this->text = txt;
    this->indecies = indecies;

    setFieldType(List);
}

ListData::ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, list<string> options) : MainFieldData(ui, fromConnection, toConnection)
{
    ListField* field = reinterpret_cast <ListField*>(ui);
    field->setData(this);
    // set text and options
    this->text = "";
    this->indecies = list<int>();
    // populate the text and options
    setTextFromList(options);
    // set the field type
    setFieldType(List);
}

void ListData::push_back(string s)
{
    // update the indecies
    this->indecies.push_back(text.length());
    // add the text
    this->text += s;
}

void ListData::push_front(string s)
{
    // update the indecies
    list<int>::iterator itr;
    for(itr = indecies.begin(); itr != indecies.end(); itr++)
    {
        (*itr) = (*itr) + s.length();
    }
    // add the index
    indecies.push_front(0);
    // add the text
    this->text = s + text;
}

void ListData::pop_back()
{
    // pop the text
    text = text.substr(0, text.length() - indecies.back() );
    // pop the index
    indecies.pop_back();
}
void ListData::pop_front()
{
    // pop the text
    text = text.substr( indecies.front() );
    // pop the index
    indecies.pop_front();
}

void ListData::insert(int index, string s)
{
    int earlyLength = 0;
    int lengthDiff = 0;
    list<int>::iterator toInsert;

    // replace the element and augment the later indecies
    list<int>::iterator itr = indecies.begin();
    for(int i=0; i < indecies.size(); i++){
        if (i < index)
        {
            earlyLength += (*itr);
        }
        else if ( i > index)
        {
            (*itr) += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = s.length();
            (*itr) += lengthDiff;
            toInsert = itr;
        }
        ++itr;
    }
    // erase the index
    indecies.insert(toInsert, earlyLength);
    // update text
    text = text.substr(0, earlyLength) + s + text.substr(earlyLength);
}

void ListData::replace(int index, string s)
{
    int earlyLength = 0;
    int lengthDiff = 0;
    list<int>::iterator toInsert;

    // replace the element and augment the later indecies
    list<int>::iterator itr = indecies.begin();
    for(int i=0; i < indecies.size(); i++){
        if (i < index)
        {
            earlyLength += (*itr);
        }
        else if ( i > index)
        {
            (*itr) += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = s.length() - (*itr);
            (*itr) += lengthDiff;
            toInsert = itr;
        }
        ++itr;
    }
    // erase the index
    indecies.insert(toInsert, earlyLength);
    indecies.erase(toInsert);
    // update text
    text = text.substr(0, earlyLength) + s + text.substr(earlyLength + s.length() - lengthDiff);
}

void ListData::erase(int index)
{
    int earlyLength = 0;
    int lengthDiff = 0;
    list<int>::iterator toErase;

    // replace the element and augment the later indecies
    list<int>::iterator itr = indecies.begin();
    for(int i=0; i < indecies.size(); i++){
        if (i < index)
        {
            earlyLength += (*itr);
        }
        else if ( i > index)
        {
            (*itr) += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = - (*itr);
            toErase = itr;
        }
        ++itr;
    }
    // erase the index
    indecies.erase(toErase);
    // update text
    text = text.substr(0, earlyLength) + text.substr(earlyLength + -lengthDiff);
}

void ListData::setTextFromList(list<string> options)
{
    qDebug() << "ListData: Setting text with options: " << options;
    text = "";
    indecies.clear();
    for(string s : options)
    {
        push_back(s);
    }
    qDebug() << "ListData: Text and indices set to: " << text << "; " << indecies;
}

list<string> ListData::toList()
{
    list<string> toReturn = {};
    list<int>::const_reverse_iterator itr;
    list<int>::const_reverse_iterator itrLast = indecies.crend();
    for (itr = indecies.crbegin(); itr != indecies.crend(); itr++)
    {
        if (itrLast != indecies.crend())
            toReturn.push_front(text.substr(*itr, *itrLast - *itr));
        else
            toReturn.push_front(text.substr(*itr));
        itrLast = itr;
    }
    return toReturn;
}

list<int> ListData::getIndecies ()
{
    return indecies;
}

void ListData::print()
{
    list<string> toPrint = toList();
    for (string s : toPrint)
    {
        qDebug() << s << "\n";
    }
}

void ListData::setIndex(int value)
{
    this->index = value;
}


int ListData::getIndex()
{
    return this->index;
}
