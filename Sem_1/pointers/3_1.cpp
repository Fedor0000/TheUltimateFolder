#include <iostream>
using namespace std;
int main()
{
    float a, b, tmp;
    float *Ptr1, *Ptr2;
    cin >> a;
    Ptr1 = &a;
    tmp = *Ptr1;
    cin >> b;
    Ptr2 = &b;
    *Ptr1 = *Ptr2;
    *Ptr2 = tmp;
    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}