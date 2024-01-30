// Перевернуть массив из N элементов, N вводит пользователь, элементы заполняются рандомом
#include <iostream>
using namespace std;
int main()
{
    int N, b;
    cin >> N;
    cout << endl;
    int arr[100];
    for (int i = 0; i < N; i++) // Рандом
    {
        arr[i] = rand();
    }
    for (int i = 0; i < N; i++) // Вывод
    {
        cout << arr[i] << endl;
    }
    cout << endl;
    for (int i = 0; i < (N/2); i++) // Переворот
    {
        b = arr[i];
        arr[i] = arr[(N - 1 - i)];
        arr[(N - 1 - i)] = b;
    }
    for (int i = 0; i < N; i++) // вывод
    {
        cout << arr[i] << endl;
    }
    return 0;
}