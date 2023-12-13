#include <iostream>
#include <string>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru_RU");
    int countC, countV;
    countC = countV = 0;
    string st;
    cin >> st;
    const char* pt = st.c_str();
    for (int i = 0; i < st.length(); i++)
    {
        if (*pt == 'А' || *pt == 'Е' || *pt == 'И' || *pt == 'О' || *pt == 'У' || *pt == 'Э' || *pt == 'Ю' || *pt == 'Я' || *pt == 'а' || *pt == 'е' || *pt == 'и' || *pt == 'о' || *pt == 'у' || *pt == 'э' || *pt == 'ю' || *pt == 'я' || *pt == 'Ы' || *pt == 'ы' || *pt == 'ё' || *pt == 'Ё')
        {
            countV++;
        }
        else { countC++; }
        pt++;
    }
    cout << "Count of vowels = " << countV << ", Count of consonaunces = " << countC;
    return 0;
}