#include "mmaster.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MMaster w;
    w.show();
    return a.exec();
}
