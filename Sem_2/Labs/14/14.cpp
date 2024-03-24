/*
Выполнить сортировку массива методом сортировки Хоара.

Массив статический и содержит 25 элементов, заполнение массива организавать любым удобным способом.
*/
#include <iostream>
using namespace std;
void ranArr(int arr[], int sizeArr, int min, int max)
{
    srand(time(0) * time(0));
    for (int i = 0; i < sizeArr; i++)
    {
        arr[i] = rand() % (max - min + 1) + min;
    }
}
void printArr(int arr[], int sizeArr)
{
    for (int i = 0; i < sizeArr; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int partitionH(int a[], int low, int high)
{
    int pivot = a[low];
    int i = low - 1;
    int j = high + 1;
    while (1)
    {
        do
        {
            i++;
        } while (a[i] < pivot);

        do
        {
            j--;
        } while (a[j] > pivot);

        if (i >= j) return j;
        swap(a[i], a[j]);
    }
}
void quickSortH(int arr[], int low, int high)
{
    if (low >= high) return;
    int pivot = partitionH(arr, low, high);
    quickSortH(arr, low, pivot);
    quickSortH(arr, pivot + 1, high);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    const int N = 25; // если изменить, работает и с другими размерами
    int arr[N];
    int min, max;
    cout << "Введите минимальное случайное число ";
    cin >> min;
    cout << "Введите максимальное случайное число ";
    cin >> max;
    ranArr(arr, N, min, max);
    cout << "Массив до сортировки:" << endl;
    printArr(arr, N);
    quickSortH(arr, 0, N-1);
    cout << "Массив после сортировки:" << endl;
    printArr(arr, N);
    return 0;
}
/*
        ТЕСТЫ
1)
Введите минимальное случайное число -7
Введите максимальное случайное число -3
Массив до сортировки:
-4 -5 -5 -6 -3 -6 -6 -7 -6 -7 -5 -7 -4 -3 -6 -4 -3 -7 -6 -5 -5 -7 -5 -5 -5
Массив после сортировки:
-7 -7 -7 -7 -7 -6 -6 -6 -6 -6 -6 -5 -5 -5 -5 -5 -5 -5 -5 -4 -4 -4 -3 -3 -3

2)
Введите минимальное случайное число -3
Введите максимальное случайное число 6
Массив до сортировки:
-3 0 4 6 0 -2 1 3 0 5 3 1 5 2 -2 0 4 -3 4 3 6 2 -2 -3 5
Массив после сортировки:
-3 -3 -3 -2 -2 -2 0 0 0 0 1 1 2 2 3 3 3 4 4 4 5 5 5 6 6

3)
Введите минимальное случайное число 4
Введите максимальное случайное число 9
Массив до сортировки:
8 8 9 9 6 7 8 5 4 9 8 5 7 4 4 5 8 9 6 5 8 4 4 6 4
Массив после сортировки:
4 4 4 4 4 4 5 5 5 5 6 6 6 7 7 8 8 8 8 8 8 9 9 9 9
*/