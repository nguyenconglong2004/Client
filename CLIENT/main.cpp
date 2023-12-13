#include "CLIENT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CLIENT w;
    w.setWindowState(Qt::WindowFullScreen);
    w.show();
    return a.exec();
}
