#include "connectiondata.h"
#include "../Dialogue/DialogueData.h"
#include "../../widgets/editor/FieldConnection/fieldconnection.h"

ConnectionData::ConnectionData(DialogueData* previous, DialogueData* next, FieldConnection* uiConnection) {
    this->previous = previous;
    this->next = next;

    this->uiConnection = uiConnection;
    connect(uiConnection->getAuto(), &QCheckBox::stateChanged, this, &ConnectionData::onAutoToggled);
}

DialogueData* ConnectionData::replacePrevious(DialogueData* previous) {
    DialogueData* old = this->previous;
    this->previous = previous;

    // TODO: Update connection in old and new

    return old;
}

DialogueData* ConnectionData::replaceNext(DialogueData* next) {
    DialogueData* old = this->next;
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
