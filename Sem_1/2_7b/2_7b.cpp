#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Введите целое число (мин. 1), которое будет являться стороной квадрата" << endl;
    cin >> n;
    if (n >= 1) //единичная звёздочка тоже своего рода квадрат один на один
    {
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
        cout << "Введёное число должно быть больше или равно единице" << endl;
    }
    return 0;
}