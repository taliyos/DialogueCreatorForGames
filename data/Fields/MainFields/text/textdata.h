#ifndef TEXTDATA_H
#define TEXTDATA_H

#include "data/Fields/MainFields/mainfielddata.h"

/// <summary>
/// This class extends MainFieldData by abstracting its text as user input.
/// </summary>

// This class is currently a stub, not sure what else it needs over the base class.
class TextData : protected MainFieldData
{
public:
    // constructors
    TextData();
    // deconstructor
    ~TextData();

};
#endif // TEXTDATA_H
