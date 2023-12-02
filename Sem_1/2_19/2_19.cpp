#include <iostream>
using namespace std;
int main()
{
    int N, sum = 0;    
    cout << "Enter the number of terms of the sequence ";
    cin >> N;
    if (N > 0)
    {
        for (int i = 1; i <= N; i++)
        {
            if (i%3==0) { sum = sum - i; }
            else { sum = sum + i; }                     
        }
        cout << "Super sum = " << sum << endl;
    }
    else { cout << "Needed minimum one element of sequence!"; }
    return 0;
}