#ifndef INPUTLISTDATA_H
#define INPUTLISTDATA_H

#include <QWidget>
#include <utility>
#include <string>
#include <list>
#include "../mainfielddata.h"

using namespace std;

/// <summary>
/// This class extends MainFieldData by abstracting its text as user input.
/// </summary>

// This class is currently a stub, not sure what else it needs over the base class.
class InputListData : public MainFieldData
{
public:
    InputListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
};

#endif // INPUTLISTDATA_H
