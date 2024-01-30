// Условие: Найти максимальный элемент массива и минимальный за один цикл
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int arr[10];
    int max, min;
    for (int i = 0; i < 10; i++)
    {
        cout << "Введите элемент массива с индесом [" << i << "] = ";
        cin >> arr[i];
    }
    cout << endl;
    max = arr[0];
    min = arr[0];
    for (int i = 1; i < 10; i++)
    {
        if (arr[i] > max) {max = arr[i];}
        if (arr[i] < min) {min = arr[i];}
    }
    cout << "Максимальный элемент массива = " << max << endl;
    cout << "Минимальный элемент массива = " << min;
    return 0;
}