// Условие: Найти максимальный элемент массива
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int arr[10];
    int max, number;
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
        }
    }
    cout << "Максимальный элемент массива arr[" << number << "] = " << max;
    return 0;
}