#include <iostream>
#include <string>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru_RU");
    int countA, counta, countothers, total;
    countA = counta = countothers = total = 0;
    string st;
    char A, a;
    cin >> st;
    cin >> A;
    cin >> a;
    const char* pt = st.c_str();
    for (int i = 0; i < st.length(); i++)
    {
        if (*pt == A) { countA++; }
        else if (*pt == a) { counta++; }
        else { countothers++; }
        pt++;
    }
    total = countA + counta + countothers;
    cout << "Count of " << A << " = " << countA << ", Count of " << a << " = " << counta << ", Count of other symbols = " << countothers << ", Total number of symbols = " << total;
    return 0;
}