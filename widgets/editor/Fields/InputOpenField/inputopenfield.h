#ifndef INPUTOPENFIELD_H
#define INPUTOPENFIELD_H

#include "data/Fields/MainFields/input/inputdata.h"
#include <QLabel>
#include <QPushButton>
#include <QWebEngineView>
#include <QWidget>

namespace Ui {
class InputOpenField;
}

/**
 * Extends QDialog to represent an open line that accepts player input.
 */
class InputOpenField : public QWidget
{
    Q_OBJECT

public:
    explicit InputOpenField(QWidget *parent = nullptr);
    ~InputOpenField();

    static QString generateHtml(const QString& content, const QString& content2, InputData* textData);
    void exportToBrowser();
    void setView(QWebEngineView* v);

    QLabel* getLabel();
    QPushButton* getPreview();

    InputData* getData();
    void setData(InputData* data);

signals:
    void previewRequested(const QString& content, const QString& content2, InputData* textData);
    void removeField(InputOpenField* field);

private:
    Ui::InputOpenField *ui;
    InputData* data = nullptr;
    void sendRemove();
};

#endif // INPUTOPENFIELD_H
