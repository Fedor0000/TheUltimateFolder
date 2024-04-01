# Лабораторная работа № 15.1 "Сортировка естественным слиянием"

## Без варианта.

### Задание

Отсортировать массив произвольного размера с произвольным заполнением с использованием сортировки естественным слиянием.

## Блок-схема

![Блок схема функций](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/15.1/jpeg's/15.1_functions.jpg)

![Блок схема main](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/15.1/jpeg's/15.1_main.jpg)

## Программа

```cpp
#include <iostream>
using namespace std;
int getIndex(int* a, int* t, int n)
{
    int cnt = 0;
    t[cnt++] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i + 1] < a[i]) t[cnt++] = i + 1;
    }
    return cnt;
}
void merge(int* a, int* b, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    while (i <= mid) b[k++] = a[i++];
    while (j <= right)	b[k++] = a[j++];
}
void mergePass(int* a, int* b, int* t, int s, int n, int cnt)
{
    int i = 0;
    while (i <= cnt - 2 * s)
    {
        if (i + 2 * s < cnt) merge(a, b, t[i], t[i + s] - 1, t[i + 2 * s] - 1);
        else merge(a, b, t[i], t[i + s] - 1, n - 1);
        i = i + 2 * s;
    }
    if (i + s < cnt)
    {
        merge(a, b, t[i], t[i + s] - 1, n - 1);
    }
    else if (i < cnt)
    {
        for (int j = t[i]; j <= n - 1; j++) b[j] = a[j];
    }
}
void mergeSort(int* a, int* t, int n, int cnt)
{
    int b[100];
    int s = 1;
    while (s < cnt)
    {
        mergePass(a, b, t, s, n, cnt);
        s += s;
        mergePass(b, a, t, s, n, cnt);
        s += s;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int n, start, end;
    cout << "Введите размер массива: ";
    cin >> n;
    while (n < 1)
    {
        cout << "Да что ты вообще вводишь?" << endl << "Введите размер массива: ";
        cin >> n;
    }
    cout << "Введите границы случайных чисел в виде: a b -> ";
    cin >> start >> end;
    while (end < start)
    {
        cout << "Да что ты вообще вводишь?" << endl << "Введите границы случайных чисел в виде: a b -> ";
        cin >> start >> end;
    }
    int* a = new int[n];
    int* t = new int[n];
    for (int i = 0; i < n; i++) a[i] = rand() % (end - start + 1) + start;
    cout << "Исходный массив:\n";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl << endl;
    int cnt = getIndex(a, t, n);
    mergeSort(a, t, n, cnt);
    cout << "Отсортированный массив:\n";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    delete[] a;
    delete[] t;
    return 0;
}
```

## Тесты текстом

1)
Введите размер массива: 25
Введите границы случайных чисел в виде: a b -> -20 20
Исходный массив:
-7 5 -6 -4 -4 -11 1 -17 -10 -14 -14 6 -11 0 8 17 -19 7 -2 -17 -2 20 3 0 3

Отсортированный массив:
-19 -17 -17 -14 -14 -11 -11 -10 -7 -6 -4 -4 -2 -2 0 0 1 3 3 5 6 7 8 17 20


2)
Введите размер массива: 29
Введите границы случайных чисел в виде: a b -> -89 0
Исходный массив:
-39 -84 -65 -21 -86 -88 -76 -34 -29 -67 -30 -81 -8 -80 -84 -30 0 -34 -41 -62 -24 -65 -55 -33 -1 -71 -35 -43 -25

Отсортированный массив:
-88 -86 -84 -84 -81 -80 -76 -71 -67 -65 -65 -62 -55 -43 -41 -39 -35 -34 -34 -33 -30 -30 -29 -25 -24 -21 -8 -1 0


3)
Введите размер массива: 5
Введите границы случайных чисел в виде: a b -> 7 7
Исходный массив:
7 7 7 7 7

Отсортированный массив:
7 7 7 7 7


## Тесты скриншоты

![Первый тест](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/15.1/screen/1.png)
![Второй тест](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/15.1/screen/2.png)
![Третий тест](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/15.1/screen/3.png)
