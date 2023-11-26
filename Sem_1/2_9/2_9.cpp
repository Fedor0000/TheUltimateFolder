#include <iostream>
using namespace std;
int main()
{
    int n, diagonal, afterspaces, inspaces, beforespaces;
    cin >> n;
    diagonal = n / 2 + 1; // Длина диагональных рёбер и высота ромба
    beforespaces = n / 2; // Пробелы перед ромбом
    afterspaces = 0; // Пробелы после ромба
    inspaces = n - 2; // Пробелы внутри квадрата и ромба
    for (int i = 1; i <= diagonal; i++) // Строит ромб
    {
        if (i == 1) // Первая строка ромба
        {
            for (int j = 1; j <= beforespaces; j++) {cout << "  ";}                
            for (int j = 1; j <= n; j++) {cout << "* ";}
            cout << endl;
            beforespaces--;
        }
        else
        {
            if (i == diagonal) // Последняя строка
            {
                for (int j = 1; j <= n; j++) {cout << "* ";}
                for (int j = 1; j <= (n / 2 - 1); j++) {cout << "  ";}
                cout << "* " << endl;
            }
            else // Остальные строки ромба
            {
                for (int j = 1; j <= beforespaces; j++) { cout << "  "; }
                cout << "* ";
                for (int j = 1; j <= inspaces; j++) { cout << "  "; }
                cout << "* ";
                for (int j = 1; j <= afterspaces; j++) { cout << "  "; }
                cout << "* " << endl;
                afterspaces++;
                beforespaces--;
            }
        }
    }
    for (int i = 1; i <= n - 1 - diagonal; i++) // Строит квадрат до перехода в сужениe
    {
        cout << "* ";
        for (int j = 1; j <= inspaces; j++) { cout << "  "; }
        cout << "* ";
        for (int j = 1; j <= afterspaces; j++) { cout << "  "; }
        cout << "* " << endl;
    }
    for (int i = 1; i <= (diagonal - 1); i++) // Оставшийся квадрат без последней строки
    {
        cout << "* ";
        for (int j = 1; j <= inspaces; j++) { cout << "  "; }
        cout << "* ";
        for (int j = 1; j <= afterspaces; j++) { cout << "  "; }
        cout << "* " << endl;
        afterspaces--;
    }
    for (int i = 1; i <= n; i++) {cout << "* ";} // Последняя строка квадрата
    cout << endl;
    return 0;
}