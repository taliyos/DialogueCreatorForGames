#include "listdata.h"
#include <iterator>
#include <qDebug>

ListData::ListData(string txt, string delim)
{
    this->text = txt;
    this->delimiter = delim;
    this->indecies = list<pair<int, int>>();
    generateIndecies();
}
void ListData::setText(string txt)
{
    this->text = txt;
    generateIndecies();
}
void ListData::setDelimiter(string delim)
{
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
    int indexStart = 1;
    int indexLength = delimiter.length();
    for (int i = indexStart + indexLength; i < text.length(); i++) {
        indexLength++;
        if (text.substr(i, delimiter.length()) == delimiter) {
            indecies.push_back({indexStart, indexLength-delimiter.length()});
            indexStart =i+1;
            indexLength = 0;
        }
    }
    indecies.push_back({indexStart, indexLength});
}

void ListData::push_back(string s)
{
    // update the indecies
    this->indecies.push_back({text.length() + 1, s.length()});
    // add the text
    this->text += delimiter + s;
}

void ListData::push_front(string s)
{
    // update the indecies
    for(pair<int, int> p : indecies)
    {
        p.first = p.first + 1 + s.length();
    }
    // add the index
    indecies.push_front({0, s.length()});
    // add the text
    this->text = delimiter + s + text;
}

void ListData::pop_back()
{
    // pop the text
    text = text.substr(0, text.length() - (indecies.back().second + 1));
    // pop the index
    indecies.pop_back();
}
void ListData::pop_front()
{
    // pop the text
    text = text.substr(indecies.front().second + 1);
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
            earlyLength += 1 + (*itr).second;
        }
        else if ( i > index)
        {
            (*itr).first += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = s.length() + 1;
            toInsert = itr;
        }
        ++itr;
    }
    // insert the text
    indecies.insert(itr, {earlyLength, s.length()});
    // update text
    text = text.substr(0, earlyLength) + delimiter + s + text.substr(earlyLength + lengthDiff);

}

void ListData::replace(int index, string s)
{
    int earlyLength = 0;
    int lengthDiff = 0;

    // replace the element and augment the later indecies
    list<pair<int, int>>::iterator itr = indecies.begin();
    for(int i=0; i < indecies.size(); i++){
        if (i < index)
        {
            earlyLength += 1 + (*itr).second;
        }
        else if ( i > index)
        {
            (*itr).first += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = (*itr).second - s.length();
            (*itr) = {earlyLength, s.length()};
        }
        ++itr;
    }
    // update text
    text = text.substr(0, earlyLength) + delimiter + s + text.substr(earlyLength + s.length());
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
            earlyLength += 1 + (*itr).second;
        }
        else if ( i > index)
        {
            (*itr).first += lengthDiff;
        }
        else if (i == index)
        {
            lengthDiff = - (1 +(*itr).second);
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
