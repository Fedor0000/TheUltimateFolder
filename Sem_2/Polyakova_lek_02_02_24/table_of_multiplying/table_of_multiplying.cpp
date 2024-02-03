// Создать Программу, выводящую таблицу умножения
#include <iostream>
using namespace std;
int main()
{
    int a[10][10];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            a[i][j] = i * j;
        }
    }
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}