#include "widgets/tabs/TabWindow/tabwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TabWindow tabWindow;
    tabWindow.show();

    return a.exec();
}
