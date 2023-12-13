#include <iostream>
using namespace std;
int main()
{
    int n, tmp, max, min, *Ptr = &tmp;
    cin >> n;
    cin >> *Ptr;
    max = *Ptr;
    min = *Ptr;
    for (int i = 2; i <= n; i++)
    {
        cin >> *Ptr;
        if (*Ptr > max) {max = *Ptr;}
        else if (*Ptr < min) {min = *Ptr;}
    }
    cout << "Max = " << max << ", Min = " << min << endl;
    return 0;
}