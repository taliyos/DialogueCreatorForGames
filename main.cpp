#include "widgets/editor/MainEditor/maineditor.h"
#include "widgets/editor/EditorTools/editortools.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainEditor editor;
    editor.show();
    return a.exec();
}