/*
1. Написать функцию для создания списка. Функция может создавать пустой список, а затем добавлять в него элементы.
2. Написать функцию для печати списка.Функция должна предусматривать вывод сообщения, если список пустой.
3. Написать функции для удаления и добавления элементов списка в соответствии со своим вариантом.
4. Выполнить изменения в списке и печать списка после каждого изменения.
5. Написать функцию для записи списка в файл.
6. Написать функцию для уничтожения списка.
7. Записать список в файл, уничтожить его и выполнить печать (при печати должно быть выдано сообщение "Список пустой").
8. Написать функцию для восстановления списка из файла.
9. Восстановить список и распечатать его.
10. Уничтожить список.

    Вариант 3.
Записи в линейном списке содержат ключевое поле типа int. Сформировать однонаправленный список. Удалить из него К элементов, начиная с заданного номера, добавить элемент перед элементом с заданным номером.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
struct ListElem
{
    int data = 0;
    ListElem* next = nullptr;
};
struct List
{
    ListElem* head = nullptr;
    int size = 0;
};
void pushBack(List& list, int data) // Добавляет элемент в конец списка
{
    ListElem* new_ListElem = new ListElem;
    new_ListElem->data = data;
    if (list.head == nullptr) list.head = new_ListElem;
    else
    {
        ListElem* currentListElem = list.head;
        while (currentListElem->next != nullptr) currentListElem = currentListElem->next;
        currentListElem->next = new_ListElem;
    }
    list.size++;
}
void createList(List& list, int colwo) // создает список из colwo элементов
{
    int tmp;
    for (int i = 1; i <= colwo; i++)
    {
        cout << "Введите значение элемента ";
        cin >> tmp;
        pushBack(list, tmp);
    }
    if (colwo != 0) cout << endl;
}
void printList(List& list) // Печатает все элементы из списка
{
    ListElem* tmp = list.head;
    if (tmp == nullptr)
    {
        cout << "Список пустой." << endl;
        return;
    }
    for (int i = 1; i <= list.size; i++)
    {
        cout << "№" << i << ". " << tmp->data << endl;
        tmp = tmp->next;
    }
    cout << endl;
}
void delElems(List& list, int n, int kol) // n - номер, с которого удаляем, k - количество удалений
{
    ListElem* tmp = list.head;
    if (tmp == nullptr)
    {
        cout << "Список пустой." << endl;
        return;
    }
    if ((n + kol - 1) > list.size)
    {
        cout << "Проверьте правильность введенных данных!";
        return;
    }
    if (n == 1)
    {
        for (int i = 1; i <= kol; i++)
        {
            ListElem* delElem = tmp;
            list.head = delElem->next;
            tmp = tmp->next;
            delete delElem;
            list.size--;
        }
    }
    else
    {
        unsigned int counter = 1;
        while (counter != n - 1)
        {
            tmp = tmp->next;
            counter++;
        }
        for (int i = 1; i <= kol; i++)
        {
            ListElem* delElem = tmp->next;
            tmp->next = delElem->next;
            delete delElem;
            list.size--;
        }
    }
}
void killer(List& list)
{
    ListElem* tmp = list.head;
    if (tmp == nullptr) return;
    for (int i = 1; i <= list.size; i++)
    {
        ListElem* delElem = tmp;
        list.head = delElem->next;
        tmp = tmp->next;
        delete delElem;
    }
    list.size = 0;
}
void adder(List& list, int nomer, int data)
{
    ListElem* tmp = list.head;
    if (tmp == nullptr)
    {
        cout << "Список пустой, данное действие невозможно." << endl;
        return;
    }
    if (nomer > list.size)
    {
        cout << "Данное действие невозможно, так как нет элемента с этим номером." << endl;
        return;
    }
    if (nomer == 1)
    {
        ListElem* new_ListElem = new ListElem;
        list.head = new_ListElem;
        new_ListElem->next = tmp;
        new_ListElem->data = data;
        list.size++;
    }
    else
    {
        unsigned int counter = 1;
        while (counter != nomer - 1)
        {
            tmp = tmp->next;
            counter++;
        }
        ListElem* new_ListElem = new ListElem;
        new_ListElem->next = tmp->next;
        tmp->next = new_ListElem;
        new_ListElem->data = data;
        list.size++;
    }
}
void saver(List& list)
{
    FILE* f;
    if ((f = fopen("file.bin", "wb")) == NULL) exit(1);
    fwrite(&list.size, sizeof(int), 1, f);
    ListElem* tmp = list.head;
    for (int i = 1; i <= list.size; i++)
    {
        fwrite(&tmp->data, sizeof(int), 1, f);
        tmp = tmp->next;
    }
    fclose(f);
}
void uploader(List& list)
{
    FILE* f;
    int data, sizzz;
    if ((f = fopen("file.bin", "rb")) == NULL) exit(2);
    fread(&sizzz, sizeof(int), 1, f);
    for (int i = 1; i <= sizzz; i++)
    {
        fread(&data, sizeof(int), 1, f);
        pushBack(list, data);
    }
    fclose(f);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int listSize, n, k;
    List spisok;
    cout << "Введите количество элементов в списке ";
    cin >> listSize;
    cout << endl;
    createList(spisok, listSize);
    printList(spisok);
    cout << "Введите номер элемента в списке и количество элементов для удаления (элементы удаляются с заданного включительно) ";
    cin >> n;
    cin >> k;
    delElems(spisok, n, k);
    printList(spisok);
    cout << "Введите номер элемента в списке перед которым нужно вставить ещё один, и значение вставляемого элемента  ";
    cin >> n;
    cin >> k;
    adder(spisok, n, k);
    printList(spisok);
    saver(spisok);
    killer(spisok);
    printList(spisok);
    uploader(spisok);
    printList(spisok);
    killer(spisok);
    printList(spisok);
    return 0;
}
/*
        ТЕСТЫ
1) Консоль:
Введите количество элементов в списке 5

Введите значение элемента 12
Введите значение элемента -876
Введите значение элемента 0
Введите значение элемента 12
Введите значение элемента 555

№1. 12
№2. -876
№3. 0
№4. 12
№5. 555

Введите номер элемента в списке и количество элементов для удаления (элементы удаляются с заданного включительно) 1 2
№1. 0
№2. 12
№3. 555

Введите номер элемента в списке перед которым нужно вставить ещё один, и значение вставляемого элемента  1 -1
№1. -1
№2. 0
№3. 12
№4. 555

Список пустой.
№1. -1
№2. 0
№3. 12
№4. 555

Список пустой.


2) Консоль:
Введите количество элементов в списке 6

Введите значение элемента 123
Введите значение элемента 987
Введите значение элемента 267
Введите значение элемента 8
Введите значение элемента -654
Введите значение элемента 222222

№1. 123
№2. 987
№3. 267
№4. 8
№5. -654
№6. 222222

Введите номер элемента в списке и количество элементов для удаления (элементы удаляются с заданного включительно) 4 3
№1. 123
№2. 987
№3. 267

Введите номер элемента в списке перед которым нужно вставить ещё один, и значение вставляемого элемента  3 33333
№1. 123
№2. 987
№3. 33333
№4. 267

Список пустой.
№1. 123
№2. 987
№3. 33333
№4. 267

Список пустой.


3) Консоль:
Введите количество элементов в списке 7

Введите значение элемента 12
Введите значение элемента 0
Введите значение элемента 0
Введите значение элемента 6666
Введите значение элемента -643
Введите значение элемента 98
Введите значение элемента 34

№1. 12
№2. 0
№3. 0
№4. 6666
№5. -643
№6. 98
№7. 34

Введите номер элемента в списке и количество элементов для удаления (элементы удаляются с заданного включительно) 2 2
№1. 12
№2. 6666
№3. -643
№4. 98
№5. 34

Введите номер элемента в списке перед которым нужно вставить ещё один, и значение вставляемого элемента  4 6666
№1. 12
№2. 6666
№3. -643
№4. 6666
№5. 98
№6. 34

Список пустой.
№1. 12
№2. 6666
№3. -643
№4. 6666
№5. 98
№6. 34

Список пустой.
*/