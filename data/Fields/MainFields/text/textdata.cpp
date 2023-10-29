#include <QWidget>
#include "textdata.h"

#include "../../../ConnectionData/connectiondata.h"
#include "../mainfielddata.h"

TextData::TextData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection) : MainFieldData(ui, fromConnection, toConnection)
{

}
