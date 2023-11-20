#ifndef INPUTLISTFIELD_H
#define INPUTLISTFIELD_H

#include "data/Fields/MainFields/input/inputlistdata.h"
#include <QListWidget>
#include <QPushButton>
#include <QWebEngineView>
#include <QWidget>

namespace Ui {
class InputListField;
}

/**
 * Extends QWidget to represent field with selectable list configs, which are then shown.
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

    QListWidget* getListWidget();
    QPushButton* getPreview();

    InputListData* getData();
    void setData(InputListData* data);
    void setIndex(int index);

    /**
     * If the given index matches, the indices and options of this field are updated in the UI and in the data.
     * @param index: the config index that is trying to be updated.
     * @param indices: the new list of selectable indices
     * @param options: the new list of selectable text options
     */
    void updateDataAndUI(int index, list<int> indices, list<string> options);

signals:
    void previewRequested(const QString& content, const QString& content2, InputListData* textData);
    void removeRequested(InputListField* field);
    /**
     * InputListFields with the given index want to be updated, sent in a signal.
     * @param index: the config index that wants to be updated.
     */
    void updateRequested(int index);

private:
    Ui::InputListField *ui = nullptr;
    InputListData* data = nullptr;
    void sendRemoveRequest();
    void sendUpdateRequest();
};

#endif // INPUTLISTFIELD_H
