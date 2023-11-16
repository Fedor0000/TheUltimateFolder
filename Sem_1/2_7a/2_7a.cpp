#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int n,r;
    float d;
    cout << "Введите целое число (из числа должен нацело вычисляться корень) звёздочек в заполненном квадрате (мин. 4)" << endl;
    cin >> n;
    d = sqrt(n);
    r = d;
    if ((n >= 4)&&(d-r==0))
    {
        n = sqrt(n); //сторона квадрата
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << "*";
            }
            cout << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "Введёное число должно быть больше или равно четырёх и из числа должен нацело извлекаться корень" << endl;
    }
    return 0;
}