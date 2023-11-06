#ifndef LISTFIELD_H
#define LISTFIELD_H

#include "data/Fields/MainFields/list/listdata.h"
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QWebEngineView>

class CharacterField;
namespace Ui {
class ListField;
}

class ListField : public QWidget
{
    Q_OBJECT

public:
    explicit ListField(QWidget *parent = nullptr);
    ~ListField();
    static QString generateHtml(const QString& content, const QString& content2, ListData* textData);
    void exportToBrowser();
    void applyCharacterEffect(int effectNumber);
    void setView(QWebEngineView* v);

    QComboBox* getComboBox();
    QPushButton* getPreview();

    ListData* getData();
    void setData(ListData* data);
    void updateUI();

signals:
    void previewRequested(const QString& content,const QString& content2, ListData* textData);
    void removeField(ListField* field);
    void updateRequested();


private:
    Ui::ListField *ui;
    ListData* data = nullptr;
    bool characterFieldAdded = false;
    CharacterField* characterField = nullptr;
    void sendRemove();
};
#endif // LISTFIELD_H
