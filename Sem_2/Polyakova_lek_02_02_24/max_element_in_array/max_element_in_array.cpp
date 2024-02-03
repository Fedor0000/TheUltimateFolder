// Найти максимальный элемент в двумерном массиве, его значение, индексы, количество макс элементов
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int imax = 0;
    int jmax = 0;
    int s = 1;
    int max;
    const int m = 8;
    const int n = 7;
    int a[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 101 - 50;
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    max = a[imax][jmax];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[imax][jmax] < a[i][j])
            {
                imax = i;
                jmax = j;
                max = a[imax][jmax];
                s = 1;
            }
            else if (max == a[i][j])
            {
                s++;
            }            
        }
    }
    if ((imax == 0) && (jmax == 0))
    {
        s--;
    }
    cout << endl << "Первый максимальный элемент массива a[" << imax << "][" << jmax << "] = " << max << ". Их количество: " << s;
    return 0;
}