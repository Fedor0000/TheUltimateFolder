// Числа Фибоначчи (функция, принимающая n, где n – порядковый номер нужного числа Фибоначчи)
// 0 1 1 2 3 5 8 13 21 34 55 ...
// f(n) = f(n - 1) + f(n - 2)
#include <iostream>
using namespace std;
int recurs(int n)
{
    switch (n)
    {
    case(1): return 0; break;
    case(2): return 1; break;
    default:
    {
        if (n >= 3)
        {
            return (recurs(n - 1) + recurs(n - 2));
        }
        break;
    }
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите натуральное число - порядковый номер числа Фибоначчи: ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cout << recurs(i) << " ";
    }    
    return 0;
}
/*
1) Ввод
1
1) Вывод
0

2) Ввод
2
2) Вывод
0 1

3) Ввод
10
3) Вывод
0 1 1 2 3 5 8 13 21 34

4) Ввод
15
4) Вывод
0 1 1 2 3 5 8 13 21 34 55 89 144 233 377
*/