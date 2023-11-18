#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <QWidget>
#include "../mainfielddata.h"

using namespace std;

/**
 * InputData extends MainFieldData, representing field where users input text.
 */
class InputData : public MainFieldData
{
public:
    /**
     * Constructs a new InputData
     * @param ui: The QWidget this data is for.
     * @param fromConnection: The connection prior to this element.
     * @param toConnection: The connection following this element.
     */
    InputData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection);
};

#endif // INPUTDATA_H
