#include <QWidget>
#include "inputdata.h"

#include "../mainfielddata.h"
#include "widgets/editor/Fields/InputOpenField/inputopenfield.h"

InputData::InputData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection) : MainFieldData(ui, fromConnection, toConnection)
{
    InputOpenField* field = reinterpret_cast <InputOpenField*>(ui);
    field->setData(this);

    setFieldType(UserList);
}
