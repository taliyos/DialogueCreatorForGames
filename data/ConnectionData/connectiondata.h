#ifndef CONNECTIONDATA_H
#define CONNECTIONDATA_H

#include <QObject>
#include <QCheckBox>
#include "../Fields/fielddata.h"
#include "../../widgets/editor/FieldConnection/fieldconnection.h"

class ConnectionData : public QObject
{
    Q_OBJECT

public:
    ConnectionData(FieldConnection* ui, FieldData* previous, FieldData* next);
    ~ConnectionData();

    /**
     * Replaces the current previous DialougeData with the newly provided data.
     * 
     * @param previous is the DialogueData occuring before this connection.
     * @return The old previous, which was removed.
    */
    FieldData* replacePrevious(FieldData* previous);

    /**
     * Replaces the current next DialougeData with the newly provided data.
     * 
     * @param next is the DialogueData occuring before this connection.
     * @return The old next, which was removed.
    */
    FieldData* replaceNext(FieldData* next);

    bool getAuto();
    FieldData* getPrevious();
    FieldData* getNext();

    /**
     * Removes this connection data, deleting all DialogueData nodes connected to next.
    */
    void removeAll();

private:
    FieldConnection* ui;

    FieldData* previous;
    FieldData* next;

    bool isAuto;

    /**
     * Updates the current "auto" state.
    */
    void onAutoToggled(int state);


};

#endif
