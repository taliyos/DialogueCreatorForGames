#include <QWidget>
#include "inputlistdata.h"

#include "../mainfielddata.h"
#include "widgets/editor/Fields/InputListField/inputlistfield.h"

InputListData::InputListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection) : MainFieldData(ui, fromConnection, toConnection)
{
    InputListField* field = reinterpret_cast <InputListField*>(ui);
    field->setData(this);

    setFieldType(UserList);
}
