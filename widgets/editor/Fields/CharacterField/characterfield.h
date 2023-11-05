#ifndef CHARACTERFIELD_H
#define CHARACTERFIELD_H

#include <QWidget>

namespace Ui {
class CharacterField;
}

class CharacterField : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterField(QWidget *parent = nullptr);
    ~CharacterField();
    QString getText() const;

private:
    Ui::CharacterField *ui;
};

#endif // CHARACTERFIELD_H
