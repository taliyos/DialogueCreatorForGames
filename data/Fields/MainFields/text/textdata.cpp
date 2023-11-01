#include <QWidget>
#include "textdata.h"

#include "../../../ConnectionData/connectiondata.h"
#include "../mainfielddata.h"
#include "widgets/editor/Fields/TextField/textfield.h"

TextData::TextData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection) : MainFieldData(ui, fromConnection, toConnection)
{
    TextField* field = reinterpret_cast <TextField*>(ui);
    field->setData(this);
}
