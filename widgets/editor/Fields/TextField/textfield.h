#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "data/Fields/MainFields/text/textdata.h"
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QWebEngineView>
class CharacterField;
namespace Ui {
class TextField;
}

class TextField : public QWidget
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = nullptr);
    ~TextField();
    static QString generateHtml(const QString& content, const QString& content2, TextData* textData);
    void exportToBrowser();
    void applyCharacterEffect(int effectNumber);
    void setView(QWebEngineView* v);

    QLineEdit* getTextField();
    CharacterField* getCharacterField();
    QPushButton* getPreview();

    TextData* getData();
    void setData(TextData* data);
    void onCharacterClicked();
    void addCharacterWidget();
    void removeCharacterWidget();

signals:
    void previewRequested(const QString& content,const QString& content2, TextData* textData);
    void removeField(TextField* field);


private:
    Ui::TextField *ui;
    TextData* data = nullptr;
    bool characterFieldAdded = false;
    CharacterField* characterField = nullptr;
    void sendRemove();
};

#endif // TEXTFIELD_H
