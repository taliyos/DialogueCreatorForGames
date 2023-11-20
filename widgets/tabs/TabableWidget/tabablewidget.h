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

    /**
     * Opens a standard Dialogue Data file (JSON)
     * @return  Whether or not the open was successful
     */
    virtual bool importJSON(QString path = "") = 0;

    /**
     * Opens a .txt file into the tabable widget
     * @return  Whether or not the open was successful
     */
    virtual bool importText() = 0;

    /**
     * Opens a .docx file into the tabable widget
     * @return  Whether or not the open was successful
     */
    virtual bool importDocx() = 0;

    /**
     * Exports the file to a user-chosen location and name.
     * @return  Whether or not the export was successful
     */
    virtual bool exportFile() = 0;

    /**
     * Imports a preset (.json) file.
     * @return Whether or not the preset was imported succesfully.
     */
    virtual bool importPreset() = 0;

    /**
     * Exports a preset to a .json file.
     * @param num - The Preset number to export
     * @return Whether or not the preset was exported succesfully.
     */
    virtual bool exportPreset(int num) = 0;

    /**
     * Returns the tab's file path
     * @return the file path
     */
    virtual const QString getFilePath() = 0;

    const QString& getFileName();

protected:
    QString filePath;
    QString fileName;

private:
    Ui::TabableWidget *ui;
};

#endif // TABABLEWIDGET_H
