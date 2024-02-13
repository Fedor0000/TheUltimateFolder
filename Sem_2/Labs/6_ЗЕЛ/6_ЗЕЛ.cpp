/* 
Задана строка, состоящая из символов.Символы объединяются в слова.Слова друг от друга отделяются одним или несколькими пробелами.Текст содержит не более 255 символов.Выполнить ввод строки, используя функцию Gets(s) и обработку строки в соответствии со своим вариантом.
Вариант 3. Напечатать все слова, которые НЕ содержат гласных букв.
*/
#include <iostream>
#include <cstring>
using namespace std;
bool vowelCheck(char bukva)
{
    bool check = false;
    char vovels[32] = { 'a', 'e', 'y', 'u', 'i', 'o', 'A', 'E', 'Y', 'U', 'I', 'O', -29, -91, -21, -96, -82, -19, -17, -88, -18, -109, -123, -101, -128, -114, -99, -97, -120, -98, -15, -16};
    for (int i = 0; i < 32; i++)
    {
        if (bukva == vovels[i])
        {
            check = true;
            break;
        }
    }
    return check;
}
int main()
{
    int start, finish;
    bool vovel;
    char str[256];
    gets_s(str);
    str[strlen(str)] = ' '; // для правильной работы моей программы строка должна закончиться пробелом
    cout << endl;
    for (int i = 0; i < strlen(str); i++)
    {
        vovel = false;
        if (str[i != ' '])
        {
            start = i;
            while (str[i] != ' ')
            {
                if (vovel == false)
                {
                    vovel = vowelCheck(str[i]);
                }
                i++;
            }
            finish = i;
            if ((!vovel)&&(str[start] != ' '))
            {
                for (int j = start; j <= finish; j++)
                {
                    cout << str[j];
                }
                cout << endl;
            }
        }
    }
    return 0;
}
/*
1) Ввод
dfghj  fjk    tgb edfvb    tgb h
1) Вывод
dfghj
fjk
tgb
tgb
h

2) Ввод
TreeeSSsss Rfd EEE   EEEeee E RellllL qwertyuiop   DDDd@#$%^&*ddDDd H
2) Вывод
Rfd
DDDd@#$%^&*ddDDd
H

3) Ввод
Здесь дж    рбтйт РУсскй    ТКСТ   И БОЛЬШИЕ Бквы ТОЖе deleted gg ggd%%%$$$ddd
3) Вывод
дж
рбтйт
ТКСТ
gg
ggd%%%$$$ddd
*/