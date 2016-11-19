#include "painterwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PainterWindow w;
    w.show();

    return a.exec();
}
