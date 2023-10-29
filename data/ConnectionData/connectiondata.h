#ifndef CONNECTIONDATA_H
#define CONNECTIONDATA_H

#include <QObject>
#include <QCheckBox>
#include "../Dialogue/DialogueData.h"
#include "../../widgets/editor/FieldConnection/fieldconnection.h"

class ConnectionData : public QObject
{
    Q_OBJECT

public:
    ConnectionData(DialogueData* previous, DialogueData* next, FieldConnection* uiConnection);

    /**
     * Replaces the current previous DialougeData with the newly provided data.
     * 
     * @param previous is the DialogueData occuring before this connection.
     * @return The old previous, which was removed.
    */
    DialogueData* replacePrevious(DialogueData* previous);

    /**
     * Replaces the current next DialougeData with the newly provided data.
     * 
     * @param next is the DialogueData occuring before this connection.
     * @return The old next, which was removed.
    */
    DialogueData* replaceNext(DialogueData* next);

    bool getAuto();

    /**
     * Removes this connection data, deleting all DialogueData nodes connected to next.
    */
    void remove();

private:
    FieldConnection* uiConnection;

    DialogueData* previous;
    DialogueData* next;

    bool isAuto;

    /**
     * Updates the current "auto" state.
    */
    void onAutoToggled(int state);


};

#endif
