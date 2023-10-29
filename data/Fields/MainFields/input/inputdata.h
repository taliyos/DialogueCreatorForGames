#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <utility>
#include <string>
#include <list>
#include "../mainfielddata.h"

using namespace std;

/// <summary>
/// This class extends MainFieldData by abstracting its text as user input.
/// </summary>

// This class is currently a stub, not sure what else it needs over the base class.
class InputData : protected MainFieldData
{
public:
    InputData();
};

#endif // INPUTDATA_H
