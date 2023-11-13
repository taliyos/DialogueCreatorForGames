#ifndef INPUTLISTFIELD_H
#define INPUTLISTFIELD_H

#include "data/Fields/MainFields/input/inputlistdata.h"
#include <QComboBox>
#include <QPushButton>
#include <QWebEngineView>
#include <QWidget>

namespace Ui {
class InputListField;
}

class InputListField : public QWidget
{
    Q_OBJECT

public:
    explicit InputListField(QWidget *parent = nullptr);
    ~InputListField();

    static QString generateHtml(const QString& content, const QString& content2, InputListData* textData);
    void exportToBrowser();
    void setView(QWebEngineView* v);

    QComboBox* getComboBox();
    QPushButton* getPreview();

    InputListData* getData();
    void setData(InputListData* data);

signals:
    void previewRequested(const QString& content, const QString& content2, InputListData* textData);
    void removeField(InputListField* field);

private:
    Ui::InputListField *ui;
    InputListData* data = nullptr;
    void sendRemove();
};

#endif // INPUTLISTFIELD_H
