#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class TextField;
}

class TextField : public QWidget
{
    Q_OBJECT

    QLineEdit* getTextField();
    QPushButton* getPreview();

public:
    explicit TextField(QWidget *parent = nullptr);
    ~TextField();
    static QString generateHtml(const QString& content);
    void exportToBrowser();

signals:
    void previewRequested(const QString& content);


private:
    Ui::TextField *ui;
};

#endif // TEXTFIELD_H
