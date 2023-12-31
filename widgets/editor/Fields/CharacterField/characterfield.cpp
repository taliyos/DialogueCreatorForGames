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

QString CharacterField::getText() const
{
    return ui->lineEdit->text();
}

void CharacterField::setText(QString text)
{
    ui->lineEdit->setText(text);
}
