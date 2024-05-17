#include "graphman.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphMan w;
    w.show();
    return a.exec();
}
