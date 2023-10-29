#ifndef SUBFIELDDATA_H
#define SUBFIELDDATA_H

#include <QWidget>
#include "../fielddata.h"

/// <summary>
/// This class extends FieldData, by...
/// </summary>

// This class is currently a stub, not sure what else it needs over the base class.
class SubFieldData : protected FieldData
{
public:
    SubFieldData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
};

#endif // SUBFIELDDATA_H
