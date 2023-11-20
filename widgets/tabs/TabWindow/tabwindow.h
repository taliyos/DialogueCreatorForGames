#ifndef TABWINDOW_H
#define TABWINDOW_H

#include "widgets/editor/MainEditor/maineditor.h"
#include "widgets/tabs/ClosableTab/closabletab.h"
#include "widgets/tabs/TabableWidget/tabablewidget.h"
#include <QMainWindow>
#include <QTabWidget>

template<> struct hash<QUuid> {
    std::size_t operator()(const QUuid& id) const noexcept {
        return (size_t) qHash(id);
    }
};

namespace Ui {
class TabWindow;
}

class TabWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TabWindow(QWidget *parent = nullptr);
    ~TabWindow();

private slots:
    // Menu Bar

    /**
     * Open a new tab with the specified file (through a file select dialog)
     */
    void on_actionOpen_triggered();

    /**
     * Save the active tab to a file.
     */
    void on_actionSave_triggered();

    /**
     * Open a file dialog to save the active tab to a file.
     */
    void on_actionSaveAs_triggered();

    /**
     * Exit the application.
     */
    void on_actionExit_triggered();

    /**
     * Create a new, blank tab.
     */
    void on_actionNew_triggered();


private:

    /**
     * Creates a new MainEditor tab, adding it to the tabs map
     * @param tabName - The name of the tab to show.
    */
    const MainEditor* createEditorTab();
    const MainEditor* createEditorTab(const QString tabName);

    /**
     * Creates a tab from an existing QWidget instance.
    */
    void createTabFromExisting(TabableWidget* widget, const QString& tabName);

    /**
     * Handles extra details when switching tabs, like when the "New Tab" tab
     * is clicked.
     * @param newTabId - The id of the tab to switch to.
     */
    void switchTab(const QUuid newTabId);

    /**
     * Closes the specified tab, removing it from the tabs map
    */
    void closeTab(const QUuid tabId);

    /**
     * Updates the attached tabs, enabling/disabling the close tab button
     * depending on the total number of tabs.
     */
    void updateTabs();



    Ui::TabWindow *ui;
    std::unordered_map<QUuid, ClosableTab*> tabs = std::unordered_map<QUuid, ClosableTab*>();
    std::unordered_map<QUuid, TabableWidget*> tabContents = std::unordered_map<QUuid, TabableWidget*>();
    QUuid currentTab;
    QWidget* currentWidget = nullptr;

    static QString newTabIconPath;
};

#endif // TABWINDOW_H
