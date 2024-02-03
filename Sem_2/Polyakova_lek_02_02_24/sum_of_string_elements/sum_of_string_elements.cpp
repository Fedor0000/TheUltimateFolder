// Найти сумму элементов в каждой строке массива
#include <iostream>
using namespace std;
int main()
{
    const int m = 8;
    const int n = 7;
    int a[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 101-50;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < m; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += a[i][j];
        }
        cout << sum << " ";
    }
    return 0;
}