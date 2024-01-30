// Условие: Перед четным элементом массива вставить -1
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
            for (int j = n - 1; j > i-1; j--)
            {
                arr[j + 1] = arr[j];
            }
            arr[i] = -1;
            i++;
            n++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}