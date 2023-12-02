#include <iostream>
using namespace std;
int main()
{
    float n, n1 = 0;
    bool flag = 1;
    while (true)
    {
        cin >> n;
        if (n == 0) { break; }
        if ((n >= n1) && (n1 != 0) && (flag)) { flag = 1; }
        else
        {
            if (n1 != 0) {flag = 0;}
        }
        cin >> n1;        
        if (n1 == 0) { break; }
        if ((n <= n1) && (flag)) { flag = 1; }
        else { flag = 0; }
    }
    if (!flag)
    {
        cout << "Numbers are not ordered in ascending order";
    }
    else
    {
        cout << "Numbers are ordered in ascending order";
    }
    return 0;
}