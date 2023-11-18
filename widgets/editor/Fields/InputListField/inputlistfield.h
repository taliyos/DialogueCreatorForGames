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

/**
 * This class...
 */
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
    void setIndex(int index);
    void updateDataAndUI(int index, list<int> indices, list<string> options);

signals:
    void previewRequested(const QString& content, const QString& content2, InputListData* textData);
    void removeRequested(InputListField* field);
    void updateRequested(int index);

private:
    Ui::InputListField *ui = nullptr;
    InputListData* data = nullptr;
    void sendRemoveRequest();
    void sendUpdateRequest();
};

#endif // INPUTLISTFIELD_H
