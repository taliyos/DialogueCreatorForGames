#ifndef TABWINDOW_H
#define TABWINDOW_H

#include "widgets/editor/MainEditor/maineditor.h"
#include <QTabWidget>

namespace Ui {
class TabWindow;
}

class TabWindow : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWindow(QTabWidget *parent = nullptr);
    ~TabWindow();

private:
    /**
     * Adds the new tab button to the end of the tab list
    */
    void addNewTabButton();

    /**
     * Creates a new MainEditor tab, adding it to the tabs list
    */
    void createEditorTab();

    /**
     * Creates a tab from an existing QWidget instance.
    */
    void createTabFromExisting(QWidget* widget, const QString& tabName);

    /**
     * Closes the specified tab, removing it from the tabs list
    */
    void closeTab();

    /**
     * Handles extra details when switching tabs, like when the "New Tab" tab
     * is clicked.
     * @param index - The index of the clicked tab.
     */
    void switchTab(int index);


    Ui::TabWindow *ui;
    static QString newTabIconPath;
};

#endif // TABWINDOW_H
