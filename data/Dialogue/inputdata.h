#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <utility>
#include <string>
#include <list>
#include "fielddata.h"

using namespace std;

// Character box -- added to base field
// List         -- replace field    -- just a list of options
// User input   -- replace field    -- doesn't have actual text storage -- prompt comes up in prior box
// Text         -- replace field (our normal)
// Add character box to prior 3 fields
// All of these will extend the text data

class InputData : protected FieldData
{
public:
    InputData();
    // deconstructor
    ~InputData();
};

#endif // INPUTDATA_H
