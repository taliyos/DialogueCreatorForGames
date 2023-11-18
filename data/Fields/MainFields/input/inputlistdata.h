#ifndef INPUTLISTDATA_H
#define INPUTLISTDATA_H

#include "widgets/editor/EditorTools/Settings/inputlistsettings.h"
#include <QWidget>

#include <data/Fields/MainFields/list/listdata.h>

using namespace std;

/**
 * InputListData extends MainFieldData, representing a list of user input options.
 */
class InputListData : public ListData
{
public:
    /**
     * Constructs a new InputListData
     * @param ui: The QWidget this data is for.
     * @param fromConnection: The connection prior to this element.
     * @param toConnection: The connection following this element.
     * @param settings: The settings this is connected to
     */
    InputListData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection, InputListSettings *settings);
    InputListSettings* getSettings();

private:
    InputListSettings *settings = nullptr;
};

#endif // INPUTLISTDATA_H
