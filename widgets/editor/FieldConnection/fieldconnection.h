#ifndef FIELDCONNECTION_H
#define FIELDCONNECTION_H

#include <QWidget>
#include <QCheckBox>

namespace Ui {
class FieldConnection;
}

class FieldConnection : public QWidget
{
    Q_OBJECT

public:
    explicit FieldConnection(QWidget *parent = nullptr);
    ~FieldConnection();

    QCheckBox* getAuto();
    void setAutoText(std::string text);

private:
    Ui::FieldConnection *ui;
};

#endif // FIELDCONNECTION_H
