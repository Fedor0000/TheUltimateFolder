#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;
const int CHAR_NUM = 256;
void calcCharTable(const string& pat, int charTable[CHAR_NUM])
{
    fill(charTable, charTable + CHAR_NUM, -1);
    for (int i = 0; i < pat.size(); i++)
    {
        charTable[static_cast<unsigned char>(pat[i])] = i;
    }
}
void boyerMooreSearch(const string& str, const string& pat)
{
    int strSize = str.size();
    int patSize = pat.size();
    int shiftTable[CHAR_NUM];
    calcCharTable(pat, shiftTable);
    int shift = 0;
    while (shift <= (strSize - patSize))
    {
        int j = patSize - 1;
        while (j >= 0 && pat[j] == str[shift + j])
        {
            j--;
        }
        if (j < 0)
        {
            cout << "Паттерн найден по индексу " << shift << endl;
            shift += (shift + patSize < strSize) ? patSize - shiftTable[static_cast<unsigned char>(str[shift + patSize])] : 1;
        }
        else
        {
            shift += max(1, j - shiftTable[static_cast<unsigned char>(str[shift + j])]);
        }
    }
}
vector<int> prefixFunc(const string& pat)
{
    vector<int> lps(pat.size(), 0);
    int len = 0;
    for (int i = 1; i < pat.size(); i++)
    {
        while (len > 0 && pat[i] != pat[len])
        {
            len = lps[len - 1];
        }
        if (pat[i] == pat[len])
        {
            len++;
        }
        lps[i] = len;
    }
    return lps;
}
void knuthMorrisPrattSearch(const string& str, const string& pat)
{
    int strSize = str.size();
    int patSize = pat.size();
    vector<int> lps = prefixFunc(pat);
    int strIdx = 0;
    int patIdx = 0;
    while (strIdx < strSize)
    {
        if (pat[patIdx] == str[strIdx])
        {
            patIdx++;
            strIdx++;
        }
        if (patIdx == patSize)
        {
            cout << "Паттерн найден по индексу " << strIdx - patIdx << endl;
            patIdx = lps[patIdx - 1];
        }
        else if (strIdx < strSize && pat[patIdx] != str[strIdx])
        {
            patIdx = patIdx != 0 ? lps[patIdx - 1] : 0;
            if (patIdx == 0)
            {
                strIdx++;
            }
        }
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    string str, pattern;
    cout << "Введите строку:\n";
    getline(cin, str);
    cout << "Введите подстроку:\n";
    getline(cin, pattern);
    cout << "\nПоиск алгоритмом Бойера-Мура:\n";
    boyerMooreSearch(str, pattern);
    cout << "\nПоиск алгоритмом Кнута-Морриса-Пратта:\n";
    knuthMorrisPrattSearch(str, pattern);
    return 0;
}
/*
        ТЕСТЫ:
1)
Введите строку:
Эггман был яичным человеком - куриная голова и человеческое тело. Он участвовал в грязной гонке с другими яичными людьми
Введите подстроку:
яич

Поиск алгоритмом Бойера-Мура:
Паттерн найден по индексу 11
Паттерн найден по индексу 106

Поиск алгоритмом Кнута-Морриса-Пратта:
Паттерн найден по индексу 11
Паттерн найден по индексу 106

2)
Введите строку:
expensive fire cliffs crayfish apocalypse
Введите подстроку:
fi

Поиск алгоритмом Бойера-Мура:
Паттерн найден по индексу 10
Паттерн найден по индексу 26

Поиск алгоритмом Кнута-Морриса-Пратта:
Паттерн найден по индексу 10
Паттерн найден по индексу 26

3)
Введите строку:
°╧_ЫъТєY╒j▌ ╜6Q╢еS├tBФ╗ФчРє@8╬¤М│╗46)ДCЕY╕83╬ТЗъв^P!▓цЕt^╙яАлИЗ;Eqу,=ФО╖сЭцп2U▌XTК$p┌(Ы█╦nzC─R╚lиvшб№┴)ё╞╔┬╦▌╧#`╣1рЦ·хш^д╩*v\|ОФ┐╠o╓PMd'8═ХЙкmu╗WПЛ3┘║▒╝[╢▄_кRЩ-Снхїй%K№VЗ&'` _╫╧Bh\эхЖi Ё╨Пoу╛С(╥?;l'6╪В"┐√╢u¤Oо╞ wЄfzз&;0Ac;)T╝*┐Дєg▐░ы█3БЪ└НРе╧764I╢уВс\╕2mц¤д}z4'"О╡│▄╤│Ум?╖~d0╩ає└┴
Введите подстроку:
ХЙ

Поиск алгоритмом Бойера-Мура:
Паттерн найден по индексу 138

Поиск алгоритмом Кнута-Морриса-Пратта:
Паттерн найден по индексу 138
*/