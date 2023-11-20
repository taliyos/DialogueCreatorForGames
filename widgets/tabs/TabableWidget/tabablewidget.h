#ifndef TABABLEWIDGET_H
#define TABABLEWIDGET_H

#include <QWidget>

namespace Ui {
class TabableWidget;
}

class TabableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabableWidget(QWidget *parent = nullptr);
    ~TabableWidget();

    /**
     * Saves the widget
     * @return Whether or not the save was successful
     */
    virtual bool save() = 0;

    /**
     * Saves the widget after prompting the user for a location
     * and filename.
     * @return Whether or not the save was successful
     */
    virtual bool saveAs() = 0;

    const QString& getFileName();

protected:
    QString filePath;
    QString fileName;

private:
    Ui::TabableWidget *ui;
};

#endif // TABABLEWIDGET_H
