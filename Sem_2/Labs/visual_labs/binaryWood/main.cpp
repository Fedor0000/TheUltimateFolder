#include "binarywoods.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BinaryWoods w;
    w.show();
    return a.exec();
}
