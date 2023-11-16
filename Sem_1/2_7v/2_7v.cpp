#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Введите целое число (мин. 3), которое будет являться стороной квадрата" << endl;
    cin >> n;
    if (n >= 3) //чтобы увидеть хоть один пробел, нужно взять минимальную сторону квадрата за 3
    {
        for (int i = 1; i <= n; i++)
        {
            if (i == 1 or i == n)
            {
                for (int j = 1; j <= n; j++)
                {
                    cout << "*";
                }
            }
            else
            {
                cout << "*";
                for (int k = 1; k <= (n - 2); k++)
                {
                    cout << " ";
                }
                cout << "*";
            }
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Введёное число должно быть больше или равно трем" << endl;
    }
    return 0;
}