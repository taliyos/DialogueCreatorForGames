#include "widgets/editor/MainEditor/maineditor.h"
#include "widgets/editor/EditorTools/editortools.h"

#include <QApplication>
#include <QWebEngineView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainEditor editor;
    editor.show();

    /*QApplication app(argc, argv);
    QWebEngineView view;
    view.load(QUrl("https://qt-project.org/"));
    view.resize(1024, 750);
    view.show();
    return app.exec();*/

    return a.exec();
}
