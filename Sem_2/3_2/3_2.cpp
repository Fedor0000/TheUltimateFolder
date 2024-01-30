// Перевернуть массив в интервале [p; q], элементы заполняются рандомом
#include <iostream>
using namespace std;
int main()
{
    int p, q, b;
    cin >> p >> q;
    cout << endl;
    int arr[10];
    for (int i = 0; i < 10; i++) // Рандом
    {
        arr[i] = rand();
    }
    for (int i = 0; i < 10; i++) // Вывод
    {
        cout << arr[i] << endl;
    }
    cout << endl;
    while (p < q) // Переворот
    {
        b = arr[p];
        arr[p] = arr[q];
        arr[q] = b;
        p++;
        q--;
    }
    for (int i = 0; i < 10; i++) // вывод
    {
        cout << arr[i] << endl;
    }
    return 0;
}