#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float a, b, c, D, x1, x2;
    cout << "Enter the coefficients of a quadratic equation of the form: ax^2 + bx + c = 0" << endl << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    cout << endl;
    D = b * b - 4 * a * c;
    if (D < 0) {cout << a << "x^2 + " << b << "x + " << c << " = 0" << endl << "This equation don't has roots."<< endl;}
    else
    {
        x1 = (-b - sqrt(D)) / (2 * a);
        x2 = (-b + sqrt(D)) / (2 * a);
        cout << a << "x^2 + " << b << "x + " << c << " = 0" << endl << "First root = "<< x1 << endl << "Second root = " << x2 << endl;
    }
    return 0;
}