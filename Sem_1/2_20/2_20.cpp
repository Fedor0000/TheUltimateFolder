#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    float n, s, a, i = 1;    
    bool having = 0;
    cin >> n >> s;
    if (n == 0) { cout << "Dividing by zero"; return 0; };
    while ((i <=n) && (!having))
    {
        a = sin(n + i / n);
        a = round(a * 10) / 10;
        if (s == a) { having = 1; }
        else { i++; }
    }
    if (having)
    {
        cout << "Subsequence has number S. Element No" << i;
    }
    else
    {
        cout << "Subsequence don't has number S.";
    }
    return 0;
}