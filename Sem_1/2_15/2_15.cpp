#include <iostream>
using namespace std;
int main()
{
    int N, S;
    bool having = 0;
    cout << "Enter your number ";
    cin >> N;
    cout << "Enter one-digited number without sign ";
    cin >> S;
    if (N > 0 and S >= 0)
    {
        while (N >= 1)
        {
            if (S == N % 10) { having = 1; }
            N = N / 10;
        }
        if (having == 1) { cout << "Your number has this one-digited number" << endl; }
        else { cout << "Your number don't has this one-digited number" << endl; }        
    }
    else
    {
        cout << "Please check entered data";
    }
    return 0;
}