#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <QWidget>
#include <string>
#include "../../fielddata.h"

using namespace std;

class CharacterData : protected FieldData
{
public:
    CharacterData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
};

#endif // CHARACTERDATA_H
