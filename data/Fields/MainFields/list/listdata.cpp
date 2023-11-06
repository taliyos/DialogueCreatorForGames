#include <QWidget>
#include "listdata.h"
#include <iterator>
#include <qDebug>

#include "../mainfielddata.h"
#include "widgets/editor/Fields/ListField/listfield.h"

ListData::ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, string txt, string delim) : MainFieldData(ui, fromConnection, toConnection)
{
    ListField* field = reinterpret_cast <ListField*>(ui);
    field->setData(this);

    this->text = txt;
    this->delimiter = delim;
    this->indecies = list<pair<int, int>>();
    generateIndecies();

    setFieldType(List);
}

ListData::ListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection) : MainFieldData(ui, fromConnection, toConnection)
{
    ListField* field = reinterpret_cast <ListField*>(ui);
    field->setData(this);
    setFieldType(List);
}

void ListData::setText(string txt)
{
    this->text = txt;
    generateIndecies();
}
void ListData::setDelimiter(string delim = baseDelimiter)
{
    this->delimiter = delim;
    generateIndecies();
}
void ListData::setDelimiterAndText(string delim = baseDelimiter, string txt = "")
{
    this->text = txt;
    this->delimiter = delim;
    generateIndecies();
}

void ListData::generateIndecies()
{
    indecies = list<pair<int,int>>();
    // force a delimiter
    if (delimiter.empty())
        delimiter = baseDelimiter;
    // force a lead delimiter
    if ( text.find(delimiter) != 0)
        text = delimiter + text;
    int indexStart = delimiter.length();
    int indexLength = 0;
    for (int i = indexStart; i < text.length(); i++) {
        if (text.substr(i, delimiter.length()) == delimiter) {
            indecies.push_back({indexStart, indexLength});
            // skip past the delimiter we just found
            i += delimiter.length();
            indexStart = i;
            indexLength = 0;
        }
        indexLength++;
    }
    indecies.push_back({indexStart, indexLength});
}

void ListData::push_back(string s)
{
    // update the indecies
    this->indecies.push_back({text.length() + delimiter.length(), s.length()});
    // add the text
    this->text += delimiter + s;
}

void ListData::push_front(string s)
{
    // update the indecies
    for(pair<int, int> p : indecies)
    {
        p.first = p.first + delimiter.length() + s.length();
    }
    // add the index
    indecies.push_front({0, s.length()});
    // add the text
    this->text = delimiter + s + text;
}

void ListData::pop_back()
{
    // pop the text
    text = text.substr(0, text.length() - (indecies.back().second + delimiter.length()));
    // pop the index
    indecies.pop_back();
}
void ListData::pop_front()
{
    // pop the text
    text = text.substr(indecies.front().second + delimiter.length());
    // pop the index
    indecies.pop_front();
}

void ListData::insert(int index, string s)
{
    int earlyLength = 0;
    int lengthDiff = 0;
    list<pair<int, int>>::iterator toInsert;

    // replace the element and augment the later indecies
    list<pair<int, int>>::iterator itr = indecies.begin();
    for(int i=0; i < indecies.size(); i++){
        if (i < index)
        {
            earlyLength += delimiter.length() + (*itr).second;
        }
        else if ( i > index)
        {
            (*itr).first += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = (delimiter.length() + s.length());
            (*itr).first += lengthDiff;
            toInsert = itr;
        }
        ++itr;
    }
    // erase the index
    indecies.insert(toInsert, {earlyLength + delimiter.length(), s.length()});
    // update text
    text = text.substr(0, earlyLength) + delimiter + s + text.substr(earlyLength);
}

void ListData::replace(int index, string s)
{
    int earlyLength = 0;
    int lengthDiff = 0;
    list<pair<int, int>>::iterator toInsert;

    // replace the element and augment the later indecies
    list<pair<int, int>>::iterator itr = indecies.begin();
    for(int i=0; i < indecies.size(); i++){
        if (i < index)
        {
            earlyLength += delimiter.length() + (*itr).second;
        }
        else if ( i > index)
        {
            (*itr).first += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = s.length() - (*itr).second;
            (*itr).first += lengthDiff;
            toInsert = itr;
        }
        ++itr;
    }
    // erase the index
    indecies.insert(toInsert, {earlyLength + delimiter.length(), s.length()});
    indecies.erase(toInsert);
    // update text
    text = text.substr(0, earlyLength) + delimiter + s + text.substr(earlyLength + delimiter.length() + s.length() - lengthDiff);
}

void ListData::erase(int index)
{
    int earlyLength = 0;
    int lengthDiff = 0;
    list<pair<int, int>>::iterator toErase;

    // replace the element and augment the later indecies
    list<pair<int, int>>::iterator itr = indecies.begin();
    for(int i=0; i < indecies.size(); i++){
        if (i < index)
        {
            earlyLength += delimiter.length() + (*itr).second;
        }
        else if ( i > index)
        {
            (*itr).first += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = - (delimiter.length() +(*itr).second);
            toErase = itr;
        }
        ++itr;
    }
    // erase the index
    indecies.erase(toErase);
    // update text
    text = text.substr(0, earlyLength) + text.substr(earlyLength + -lengthDiff);
}

list<string> ListData::toList()
{
    if (delimiter.empty())
        return {text};
    if ( text.find(delimiter) != 0)
        text = delimiter + text;

    list<string> toReturn = {};
    size_t pos = 0;
    string token;
    string textCpy = text.substr(delimiter.size());
    while ((pos = textCpy.find(delimiter)) != std::string::npos) {
        token = textCpy.substr(0, pos);
        toReturn.push_back(token);
        textCpy.erase(0, pos + delimiter.length());
    }
    toReturn.push_back(textCpy);
    return toReturn;
}

list<pair<int, int>> ListData::getIndecies ()
{
    return indecies;
}

void ListData::print()
{
    int count = 0;
    for (pair<int, int> p : getIndecies())
    {
        qDebug() << p << " " << getText().substr(p.first, p.second) <<" " <<count << "\n";
        count++;
    }
}

const int ListData::getID()
{
    return 2;
}
