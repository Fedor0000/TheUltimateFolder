#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float n, a, max = -1;
    int i = 1, maxes = 0;
    cin >> n;
    while (i <= n)
    {
        a = sin(n + i / n);
        a = round(a * 10) / 10;
        if (a > max)
        {
            max = a;
            maxes = 0;
        }
        if (a == max)
        {
            maxes++;
        }
        i++;
    }
    cout << "Number of maxes = " << maxes;
    return 0;
}