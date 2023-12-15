/*
    Вариант 9
    x - 1 / (3 + sin(3.6 * x)) = 0
    Отрезок [0; 0.85]
    Эпсилон: eps = 0.000001
    
    Производная: f'(x) = 1 + (3.6 * cos(3.6 * x)) / pow((3 + sin(3.6 * x)), 2)
    Производная': f''(x) = (-12.96 * sin(3.6 * x) * (3 + sin(3.6 * x)) - 25.92 * pow(cos(3.6 * x), 2)) / pow((3 + sin(3.6 * x)), 3)

    Выберем правильный конец отрезка, тот, где истинно условие: f(x) * f''(x) > 0
    A: (a - 1 / (3 + sin(3.6 * a))) * (-12.96 * sin(3.6 * a) * (3 + sin(3.6 * a)) - 25.92 * pow(cos(3.6 * a), 2)) / pow((3 + sin(3.6 * a)), 3) = 0.32

    B: (b - 1 / (3 + sin(3.6 * b))) / pow((3 + sin(3.6 * b)), 2) * (-12.96 * sin(3.6 * b) * (3 + sin(3.6 * b)) - 25.92 * pow(cos(3.6 * b), 2)) / pow((3 + sin(3.6 * b)), 3) = -0.054851
    Это будет А
*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double a = 0.0, b = 0.85, eps = 0.000001, xprev, x;
    xprev = b;
    x = a;
    while (abs(x - xprev) > eps)
    {
        xprev = x;
        x = xprev - (xprev - 1 / (3 + sin(3.6 * xprev))) / (1 + (3.6 * cos(3.6 * xprev)) / pow((3 + sin(3.6 * xprev)), 2));
    }
    cout << "A = " << xprev << ", B = " << x << endl;
    return 0;
}