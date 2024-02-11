/*
Приближенно вычислить значение функции двумя способами:
1) Через сумму функционального ряда с помощью рекурсивной функции. Аргументы функции — n и x, где n — количество членов ряда, x — переменная.
2) Через прямое вычисление значения функции. Аргумент функции — переменная x.
Сравнить полученные результаты
Вариант 3
s = x - (x^3)/factorial(3)+(x^5)/factorial(5)+ ... + (-1)^n*(x^(2n+1))/factorial(2n+1)
   n=0   n=1                  n=2                        n=n
*/
#include <iostream>
#include <cmath>
using namespace std;
double recurSum = 0;
int factorial(int a)
{
    int f = 1;
    for (int i = 1; i <= a; i++)
    {
        f *= i;
    }
    return f;
}
double func(double x, int n)
{
    return (pow(-1, n) * pow(x, (2*n + 1)) / factorial(2 * n + 1));
}
double recurFunc(double x, int n)
{
    double a;
    if (n == 0)
    {
        recurSum += x;
        return x;
    }
    else
    {
        a = (recurFunc(x, n - 1) * (-1) * pow(x, 2) / (2 * n * (2 * n + 1)));
        recurSum += a;
        return a;
    }
}
int main()
{
    int n;
    double x, sum = 0;
    cout << "X = ";
    cin >> x;
    cout << "N = ";
    cin >> n;
    for (int i = 0; i <= n; i++)
    {
        sum += func(x, i);
    }
    cout << sum << endl;
    recurFunc(x, n);
    cout << recurSum;
    return 0;
}
/*
1) Ввод
X = 1
N = 5
1) Вывод
0.841471
0.841471
2) Ввод
X = 5.4
N = 3
2) Вывод
-9.14622
-9.14622
3) Ввод
X = -89.3
N = 0
3) Вывод
-89.3
-89.3
*/