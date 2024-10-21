#ifndef MATRIXXX_H
#define MATRIXXX_H

#include <vector>

class Matrixxx
{
public:
    std::vector<std::vector<bool>> matrix;
    Matrixxx() {};
    Matrixxx(unsigned long long int size);
    std::vector<bool>& operator[](unsigned long long int);
    Matrixxx& operator=(const Matrixxx& a)
    {
        if (this == &a) return *this;
        matrix = a.matrix;
        return *this;
    }
    unsigned long long int size();
};

#endif // MATRIXXX_H
