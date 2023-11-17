#ifndef TABWINDOW_H
#define TABWINDOW_H

#include "widgets/editor/MainEditor/maineditor.h"
#include "widgets/tabs/ClosableTab/closabletab.h"
#include <QWidget>
#include <QTabWidget>

template<> struct hash<QUuid> {
    std::size_t operator()(const QUuid& id) const noexcept {
        return (size_t) qHash(id);
    }
};

namespace Ui {
class TabWindow;
}

class TabWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TabWindow(QWidget *parent = nullptr);
    ~TabWindow();

private:

    /**
     * Creates a new MainEditor tab, adding it to the tabs map
    */
    void createEditorTab();

    /**
     * Creates a tab from an existing QWidget instance.
    */
    void createTabFromExisting(QWidget* widget, const QString& tabName);

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
    QUuid currentTab;

    static QString newTabIconPath;
};

#endif // TABWINDOW_H
