#include <iostream>
using namespace std;
int main()
{
    int a, b;
    int *aPtr, *bPtr;
    cin >> a >> b;
    aPtr = &a;
    bPtr = &b;
    cout << "a + b = " << (*aPtr + *bPtr) << endl;
    return 0;
}