#include "characterfield.h"
#include "ui_characterfield.h"

CharacterField::CharacterField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CharacterField)
{
    ui->setupUi(this);
}

CharacterField::~CharacterField()
{
    delete ui;
}
