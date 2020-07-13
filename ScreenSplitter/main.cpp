#include "ScreenSplitter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenSplitter w;
    w.show();
    return a.exec();
}
