#ifndef TEXTDATA_H
#define TEXTDATA_H

#include <QWidget>
#include "../mainfielddata.h"

/// <summary>
/// This class extends MainFieldData by abstracting its text as user input.
/// </summary>

// This class is currently a stub, not sure what else it needs over the base class.
class TextData : public MainFieldData
{
public:
    // constructors
    TextData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
    // deconstructor
    ~TextData();

};
#endif // TEXTDATA_H
