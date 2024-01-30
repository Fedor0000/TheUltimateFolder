// Условие: Удалить нечетный элемент
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int arr[100];
    int n;
    cout << "Введите число элементов массива (менее 50) ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Введите элемент массива с индесом [" << i << "] = ";
        cin >> arr[i];
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        if ((arr[i] % 2) == 0)
        {
            for (int j = i; j < n - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            i--;
            n--;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}