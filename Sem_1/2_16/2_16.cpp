#include <iostream>
using namespace std;
int main()
{
    int N, term, sum = 0;
    bool sign = 1;
    cout << "Enter the number of terms of the sequence ";
    cin >> N;
    if (N > 0)
    {
        for (int i = 1; i <= N; i++)
        {
            if (sign == 1) { term = -i; }
            else { term = i; }
            sum = sum + term;
            if (sign == 1) { sign = 0; }
            else { sign = 1; }
        }
        cout << "Super sum = " << sum << endl;
    }
    else {cout << "Needed minimum one element of sequence!";}
    return 0;
}