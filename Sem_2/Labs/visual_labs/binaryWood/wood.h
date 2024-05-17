#include <QChar>
#ifndef WOOD_H
#define WOOD_H

class Wood
{
public:
    Wood();
    ~Wood();
    QChar* data; // данные узла дерева
    Wood* left; // указатель на левое поддерево
    Wood* right; // указатель на правое поддерево
    int dataSize = 0; // размер массива символов
    int depth = 0; // глубина дерева (задействованно только для первого дерева, в теории, можно считать глубину для каждого поддерева)
};

#endif // WOOD_H
