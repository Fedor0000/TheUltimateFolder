#include <iostream>
using namespace std;
int main()
{
    int a, n;
    bool zeroed = true;
    bool sign;
    cout << "Введите количество элементов в последовательности ";
    cin >> a;
    if (a <= 0)
    {
        cout << "В последовательности должно быть хотя бы одно число!";
    }
    else
    {
        for (int i = 1; i <= a; i++)
        {
            cout << "Введите элемент последовательности ";
            cin >> n;
            if (n > 0 and zeroed == true)
            {
                sign = false;
            }
            else
            {
                if (n < 0 and zeroed == true)
                {
                    sign = true;
                }
            }
            if (n != 0)
            {
                zeroed = false;
            }
        }
        cout << "Первое число ";
        if (zeroed == true)
        {
            cout << "ноль, как и все остальные" << endl;
        }
        else
        {
            if (sign != true)
            {
                cout << "положительное +" << endl;
            }
            else
            {
                cout << "отрицательное -" << endl;
            }
        }
    }
	return 0;
}