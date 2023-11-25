#include <iostream>
using namespace std;
int main()
{
    int a, n, max = 0;
    cout << "Введите количество элементов в последовательности ";
    cin >> a;
    for (int i = 1; i <= a; i++)
    {
        cout << "Введите элемент последовательности ";
        cin >> n;
        if (n > max)
        {
            max = n;
        }
    }
    cout << "Максимальный элемент равен " << max;
    return 0;
}