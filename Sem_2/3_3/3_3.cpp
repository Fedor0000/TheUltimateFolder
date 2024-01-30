// Циклически cдвинуть массив на k элементов влево
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int k, tmp = 0;
    const int n = 10;
    cout << "Введите элемент массива, который будет первым ";
    cin >> k;
    cout << endl;
    int arr[10];
    for (int i = 0; i < 10; i++) // Наполнение массива
    {
        cout << "Введите элемент массива с индесом [" << i << "] = ";
        cin >> arr[i];
    }
    cout << endl;
    for (int i = 0; i < k-1; i++) // Сдвиг
    {
        tmp = arr[0];
        for (int j = 0; j < n-1; j++)
        {
            arr[j] = arr[j + 1];
        }
        arr[n-1] = tmp;
    }
    for (int i = 0; i < 10; i++) // вывод
    {
        cout << arr[i] << "  ";
    }
    return 0;
}