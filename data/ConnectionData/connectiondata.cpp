#include "connectiondata.h"
#include "../Fields/fielddata.h"
#include "../../widgets/editor/FieldConnection/fieldconnection.h"

ConnectionData::ConnectionData(FieldData* previous, FieldData* next, FieldConnection* uiConnection) {
    this->previous = previous;
    this->next = next;

    this->uiConnection = uiConnection;
    connect(uiConnection->getAuto(), &QCheckBox::stateChanged, this, &ConnectionData::onAutoToggled);
}

FieldData* ConnectionData::replacePrevious(FieldData* previous) {
    FieldData* old = this->previous;
    this->previous = previous;

    // TODO: Update connection in old and new

    return old;
}

FieldData* ConnectionData::replaceNext(FieldData* next) {
    FieldData* old = this->next;
    this->next = next;

    // TODO: Update connection in old and new

    return old;
}

bool ConnectionData::getAuto() {
    return isAuto;
}

void ConnectionData::remove() {
    if (next != nullptr) {
        //next->remove(); Action not supported yet.
    }

    delete uiConnection;
    delete this;
    
}

void ConnectionData::onAutoToggled(int state) {
    qInfo("AUTO CLICKED!");
    if (state == Qt::Unchecked || state == Qt::PartiallyChecked) isAuto = false;
    else isAuto = true;
}
