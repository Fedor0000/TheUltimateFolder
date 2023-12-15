/*
    Вариант 9
    x - 1 / (3 + sin(3.6 * x)) = 0
    Отрезок [0; 0.85]
    Эпсилон: eps = 0.000001
*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double a = 0.0, b = 0.85, eps = 0.000001, c;
    while (abs(a - b) > eps)
    {
        c = (a + b) / 2;
        if ((a - 1 / (3 + sin(3.6 * a))) * (c - 1 / (3 + sin(3.6 * c))) < 0) {b = c;}
        else if ((b - 1 / (3 + sin(3.6 * b))) * (c - 1 / (3 + sin(3.6 * c))) < 0) {a = c;}
        else {cout << "Что-то не так";}
    }
    cout << "A = " << a << ", B = " << b << endl;
    return 0;
}