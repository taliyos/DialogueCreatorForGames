#include "listdata.h"
#include <iterator>

ListData::ListData(string txt, string delim)
{
    this->text = txt;
    this->delimiter = delim;
    this->indecies = list<pair<int, int>>();
    generateIndecies();
}

void ListData::generateIndecies()
{
    indecies = list<pair<int,int>>();
    int indexLength = 0;
    for (int i = delimiter.length(); i < text.length(); i++) {
        indexLength++;
        if (text.substr(i, delimiter.length()) == delimiter) {
            indecies.push_back({i, indexLength-delimiter.length()});
            indexLength = 0;
        }
    }
    indecies.push_back({text.length()-indexLength, indexLength-delimiter.length()});
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

void ListData::pop_back(string s)
{
    // pop the text
    text = text.substr(0, text.length() - (indecies.back().second + 1));
    // pop the index
    indecies.pop_back();
}
void ListData::pop_front(string s)
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
            indecies.insert(itr, {earlyLength, s.length()});
        }
        ++itr;
    }
    // update text
    text = text.substr(0, earlyLength) + delimiter + s + text.substr(earlyLength + s.length() + 1);
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
    text = text.substr(0, earlyLength) + delimiter + s + text.substr(earlyLength + s.length() + 1);
}

void ListData::erase(int index)
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
            lengthDiff = -(*itr).second;
        }
        ++itr;
    }
    // update text
    text = text.substr(0, earlyLength) + text.substr(earlyLength + -lengthDiff + 1);
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
