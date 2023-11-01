#ifndef MAINFIELDDATA_H
#define MAINFIELDDATA_H

#include <QWidget>
#include "../fielddata.h"


/// <summary>
/// This class extends FieldData, adding nessecary UI elements.
/// </summary>

class MainFieldData : public FieldData
{
public:
    MainFieldData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
protected:
    // the character data possibly connected to this field
    CharacterData* character;
};

#endif // MAINFIELDDATA_H
