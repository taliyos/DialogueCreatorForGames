#ifndef MAINFIELDDATA_H
#define MAINFIELDDATA_H

#include "data/Fields/fielddata.h"


/// <summary>
/// This class extends FieldData, adding nessecary UI elements.
/// </summary>

class MainFieldData : protected FieldData
{
public:
    MainFieldData();
    bool getIsAuto();
    void setIsAuto(bool value);
protected:
    // whether the field is toggled to auto
    bool isAuto;
    // the character data possibly connected to this field
    CharacterData* character;
};

#endif // MAINFIELDDATA_H
