#ifndef FIELDCONNECTION_H
#define FIELDCONNECTION_H

#include <QWidget>

namespace Ui {
class FieldConnection;
}

class FieldConnection : public QWidget
{
    Q_OBJECT

public:
    explicit FieldConnection(QWidget *parent = nullptr);
    ~FieldConnection();

private:
    Ui::FieldConnection *ui;
};

#endif // FIELDCONNECTION_H
