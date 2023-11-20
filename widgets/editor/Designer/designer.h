#ifndef DESIGNER_H
#define DESIGNER_H

#include <QPushButton>
#include <QWidget>
#include <QWebEngineView>

class FieldConnection;
class TextField;
class ListField;

namespace Ui {
class Designer;
}

class Designer : public QWidget
{
    Q_OBJECT

public:
    explicit Designer(QWidget *parent = nullptr);
    ~Designer();

    FieldConnection* createFieldConnection();
    TextField* createTextField();
    ListField* createListField();

    void removeWidget(QWidget* widget);

    // Getters
    QPushButton* getCreateField();
    QPushButton* getExport();
    QWebEngineView* getPreview();

private:
    Ui::Designer *ui;
};

#endif // DESIGNER_H
