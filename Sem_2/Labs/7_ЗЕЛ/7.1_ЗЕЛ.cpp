/*
3 Вариант.
Написать перегруженные функции и основную программу,
которая их вызывает.
а) для умножения целых чисел;
б) для умножения комплексных чисел.
*/
#include <iostream>
using namespace std;
void func(double a, double b)
{
    cout << endl << (a * b);
}
void func(double a, double b, double c, double d)
{
    double real, imaginary;
    real = a * c - b * d;
    imaginary = b * c + a * d;
    if (imaginary > 0) cout << endl << real << " + " << imaginary << "i";
    else if (imaginary == 0) cout << endl << real;
    else cout << endl << real << imaginary << "i";
}
int main()
{
    setlocale(LC_ALL, "Russian");
    double a, b, c, d;
    cout << "Введите коэффициенты выражений по порядку:\na * b\n(a + bi) * (c + di)\n";
    cin >> a >> b >> c >> d;
    func(a, b);
    cout << endl;
    func(a, b, c, d);
    cout << endl;
    return 0;
}
/*
1) Тест 1
Введите коэффициенты выражений по порядку:
a * b
(a + bi) * (c + di)
12.34
35
78.7
-9

431.9

1286.16 + 2643.44i

2) Тест 2
Введите коэффициенты выражений по порядку:
a * b
(a + bi) * (c + di)
12.5
78.6
-65
-93.5

982.5

6536.6-6277.75i

3) Тест 3
Введите коэффициенты выражений по порядку:
a * b
(a + bi) * (c + di)
12.4
0
-67.5
0

0

-837
*/