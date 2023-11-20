#include <QWidget>
#include "inputlistdata.h"

#include "widgets/editor/Fields/InputListField/inputlistfield.h"

InputListData::InputListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, InputListSettings* settings) : ListData(ui, fromConnection, toConnection)
{
    InputListField* field = reinterpret_cast <InputListField*>(ui);
    this->settings = settings;
    field->setData(this);

    setFieldType(UserList);
}

InputListSettings* InputListData::getSettings()
{
    return settings;
}
