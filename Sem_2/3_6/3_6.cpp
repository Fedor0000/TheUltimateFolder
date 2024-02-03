// Условие: Найти максимальный элемент массива и их количество
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int arr[10];
    int max, number = 0, maxes = 1;
    for (int i = 0; i < 10; i++)
    {
        cout << "Введите элемент массива с индесом [" << i << "] = ";
        cin >> arr[i];
    }
    cout << endl;
    max = arr[0];
    for (int i = 1; i < 10; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            number = i;
            maxes = 1;
        }
        else if (arr[i] == max)
        {
            maxes++;
        }
    }
    cout << "Первый максимальный элемент массива arr[" << number << "] = " << max << endl;
    cout << "Количество максимальных элементов в массиве = " << maxes;
    return 0;
}