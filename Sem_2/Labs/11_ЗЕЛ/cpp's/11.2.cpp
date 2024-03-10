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
    ListElem* prev = nullptr;
};
struct List
{
    ListElem* head = nullptr;
    ListElem* tail = nullptr;
    int size = 0;
};
void pushBack(List& list, int data) // Добавляет элемент в конец списка
{
    ListElem* new_ListElem = new ListElem;
    new_ListElem->data = data;
    if (list.head == nullptr)
    {
        list.head = new_ListElem;
        list.tail = new_ListElem;
    }
    else
    {
        ListElem* currentListElem = list.head;
        while (currentListElem->next != nullptr) currentListElem = currentListElem->next;
        currentListElem->next = new_ListElem;
        new_ListElem->prev = currentListElem;
        list.tail = new_ListElem;
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
void delE(List& list, int n) // n - номер, с которого удаляем, k - количество удалений
{
    ListElem* tmp = list.head;
    if (tmp == nullptr)
    {
        cout << "Список пустой." << endl;
        return;
    }
    if (n > list.size)
    {
        cout << "Проверьте правильность введенных данных!" << endl;
        return;
    }
    unsigned int counter = 0;
    int from_tail = list.size - 1 - n;
    if (n < from_tail)
    {
        tmp = list.head;
        while (counter != n-1)
        {
            tmp = tmp->next;
            counter++;
        }
    }
    else
    {
        tmp = list.tail;
        while (counter != from_tail+1)
        {
            tmp = tmp->prev;
            counter++;
        }
    }
    ListElem* delElem = tmp;
    if ((tmp->next != nullptr) && (tmp->prev != nullptr)) // в середине
    {
        tmp = tmp->prev;
        tmp->next = delElem->next;
        tmp = delElem->next;
        tmp->prev = delElem->prev;
    }
    else if ((tmp->next == nullptr) && (tmp->prev != nullptr)) // последний, но не первый
    {
        list.tail = tmp->prev;
        tmp = tmp->prev;
        tmp->next = nullptr;
        delete delElem;
    }
    else if ((tmp->next != nullptr) && (tmp->prev == nullptr)) // первый, но не последний
    {
        list.head = tmp->next;
        tmp = tmp->next;
        tmp->prev = nullptr;
        delete delElem;
    }
    else // единственный
    {
        delete delElem;
        list.head = nullptr;
        list.tail = nullptr;
    }
    list.size--;
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
    list.tail = nullptr;
}
void adder(List& list, int n, int data)
{
    ListElem* tmp = list.head;
    if (tmp == nullptr)
    {
        cout << "Список пустой." << endl;
        return;
    }
    if (n > list.size)
    {
        cout << "Проверьте правильность введенных данных!" << endl;
        return;
    }
    unsigned int counter = 0;
    int from_tail = list.size - 1 - n;
    if (n < from_tail)
    {
        tmp = list.head;
        while (counter != n - 1)
        {
            tmp = tmp->next;
            counter++;
        }
    }
    else
    {
        tmp = list.tail;
        while (counter != from_tail + 1)
        {
            tmp = tmp->prev;
            counter++;
        }
    }
    ListElem* new_Elem = new ListElem;
    if ((tmp->next != nullptr) && (tmp->prev != nullptr)) // в середине
    {
        tmp->prev->next = new_Elem;
        new_Elem->prev = tmp->prev;
        tmp->prev = new_Elem;
        new_Elem->next = tmp;
    }
    else if ((tmp->next == nullptr) && (tmp->prev != nullptr)) // последний, но не первый
    {
        new_Elem->prev = tmp->prev;
        tmp->prev->next = new_Elem;
        tmp->prev = new_Elem;
        new_Elem->next = tmp;
        tmp->next = nullptr;
        list.tail = tmp;
    }
    else if ((tmp->next != nullptr) && (tmp->prev == nullptr)) // первый, но не последний
    {
        tmp->prev = new_Elem;
        new_Elem->next = tmp;
        list.head = new_Elem;
    }
    else // единственный
    {
        list.head = new_Elem;
        list.tail = tmp;
        new_Elem->next = tmp;
        tmp->prev = new_Elem;
    }
    new_Elem->data = data;
    list.size++;
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
    for (int i = 1; i <= k; i++) delE(spisok, n);
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