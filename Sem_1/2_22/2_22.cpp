#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float n, a, max = -1;
    int No = 0, i = 1;
    cin >> n;
    while (i <= n)
    {
        a = sin(n + i / n);
        if (a > max)
        {
            max = a;
            No = i;
        }
        i++;
    }
    cout << "Maximal number = " << max << ", his No = " << No;
    return 0;
}