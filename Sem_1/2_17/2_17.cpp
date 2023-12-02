#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float x, sum = 1;
    unsigned int n, fctrl = 1;
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
    {
        fctrl = fctrl * i;
        sum = sum + pow(x, i)/fctrl;        
    }
    cout << "Sum = " << sum;
    return 0;
}