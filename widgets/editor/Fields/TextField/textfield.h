#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "data/Fields/MainFields/text/textdata.h"
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class TextField;
}

class TextField : public QWidget
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = nullptr);
    ~TextField();

    QLineEdit* getTextField();
    QPushButton* getPreview();

    TextData* getData();
    void setData(TextData* data);

signals:
    void removeField(TextField* field);

private:
    Ui::TextField *ui;
    TextData* data = nullptr;

    void sendRemove();
};

#endif // TEXTFIELD_H
