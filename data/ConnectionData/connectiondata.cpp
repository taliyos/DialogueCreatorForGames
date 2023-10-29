#include "connectiondata.h"
#include "../Fields/fielddata.h"
#include "../../widgets/editor/FieldConnection/fieldconnection.h"

ConnectionData::ConnectionData(FieldConnection* ui, FieldData* previous, FieldData* next) {
    this->ui = ui;
    
    this->previous = previous;
    this->next = next;

    connect(ui->getAuto(), &QCheckBox::stateChanged, this, &ConnectionData::onAutoToggled);
}

ConnectionData::~ConnectionData() {
    if (ui != nullptr) {
        delete ui;
    }
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

FieldData* ConnectionData::getPrevious() {
    return previous;
}

FieldData* ConnectionData::getNext() {
    return next;
}

FieldConnection* ConnectionData::getUi() {
    return ui;
}

void ConnectionData::removeAll() {
    if (next != nullptr) {
        next->removeAll();
    }

    delete this;    
}

void ConnectionData::onAutoToggled(int state) {
    if (state == Qt::Unchecked || state == Qt::PartiallyChecked) isAuto = false;
    else isAuto = true;
}
