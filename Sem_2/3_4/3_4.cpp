// Проверить, упорядочен ли массив целых чисел по возрастанию. 
// Условие: задан одномерный массив целых чисел. Проверить, упорядочен ли он по возрастанию.
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int arr[10];
    bool boo = true;
    for (int i = 0; i < 10; i++)
    {
        cout << "Введите элемент массива с индесом [" << i << "] = ";
        cin >> arr[i];
    }
    cout << endl;
    for (int i = 0; i < 9; i++)
    {
        if (!(arr[i] < arr[i + 1]))
        {
            boo = false;
        }        
    }
    if (boo)
    {
        cout << "Идут по возрастанию";
    }
    else
    {
        cout << "Не идут по возрастанию";
    }
    return 0;
}