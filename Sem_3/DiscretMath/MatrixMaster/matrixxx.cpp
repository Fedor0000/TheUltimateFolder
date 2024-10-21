#include "matrixxx.h"

Matrixxx::Matrixxx(unsigned long long int size)
{
    std::vector<std::vector<bool>> m(size);
    std::vector<bool> a(size, 0);
    for (size_t i = 0; i < size; i++)
    {
        m[i] = a;
    }
    matrix = m;
}

std::vector<bool>& Matrixxx::operator[](unsigned long long int index)
{
    if (index >= matrix.size()) throw std::exception();
    return matrix[index];
}

unsigned long long int Matrixxx::size()
{
    return matrix.size();
}
