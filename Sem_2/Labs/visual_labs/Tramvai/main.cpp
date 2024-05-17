#include "tramvai.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tramvai w;
    w.show();
    return a.exec();
}
