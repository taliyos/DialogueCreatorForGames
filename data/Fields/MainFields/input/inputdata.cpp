#include <QWidget>
#include "inputdata.h"

#include "../mainfielddata.h"

InputData::InputData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection) : MainFieldData(ui, fromConnection, toConnection)
{
    setFieldType(UserPrompt);
}
