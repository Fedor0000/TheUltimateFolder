/*
    Вариант 9
    x - 1 / (3 + sin(3.6 * x)) = 0
    Отрезок [0; 0.85]
    Эпсилон: eps = 0.000001

    phi(x) = 1 / (3 + sin(3.6 * x))
    phi'(x) = (-3.6 * cos(3.6 * x)) / (pow((3 + sin(3.6 * x)), 2))
    |phi'(a)| = 0.4 < 1        |
    |phi'(b)| = 0.377859 < 1   | Функция нам подходит
*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double a = 0.0, b = 0.85, eps = 0.000001, xprev, x;
    x = (a + b) / 2;
    xprev = b;
    while (abs(x - xprev) > eps)
    {
        xprev = x;
        x = 1 / (3 + sin(3.6 * xprev));
    }
    cout << "A = " << xprev << ", B = " << x << endl;
    return 0;
}