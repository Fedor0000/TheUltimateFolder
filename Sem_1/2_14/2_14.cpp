#include <iostream>
using namespace std;
int main()
{
    long long int N;
    int sum = 0;
    cout << "Enter your number: ";
    cin >> N;
    while (N >= 1)
    {
        sum = sum + N % 10;
        N = N / 10;
    }
    cout << "Sum of symbols in your number = " << sum << endl;
    return 0;
}