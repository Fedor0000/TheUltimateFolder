// Заполнить квадратный массив ромбом из единичек, остальные элементы равны нулю.
#include <iostream>
using namespace std;
int main()
{
    const int n = 9;
    int mid = n / 2;
    int x = mid + 1;
    int y = mid - 1;
    int a[n][n] = {0};
    for (int i = 0; i < n; i++)
    {
        if (i <= mid)
        {
            x--;
            y++;
        }
        else
        {
            x++;
            y--;
        }
        a[i][x] = 1;
        a[i][y] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}