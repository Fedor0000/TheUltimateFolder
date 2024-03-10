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
struct StackElem
{
    int data = 0;
    StackElem* downer = nullptr;
};
struct Stack
{
    StackElem* top = nullptr;
    int size = 0;
    void push(int data)
    {
        StackElem* newElem = new StackElem;
        newElem->data = data;
        newElem->downer = top;
        top = newElem;
        size++;
    }
    int pop()
    {
        if (size == 0)
        {
            cout << "Стек пуст, действие невозможно" << endl;
            return NULL;
        }
        int value = top->data;
        StackElem* tmp = top;
        top = top->downer;
        size--;
        delete tmp;
        return value;
    }
};
void createStack(Stack& stolb, int size)
{
    int data;
    for (int i = 1; i <= size; i++)
    {
        cout << "Введите элемент стека ";
        cin >> data;
        stolb.push(data);
    }
}
void printStack(Stack& s)
{
    if (s.size == 0)
    {
        cout << "Стек пуст." << endl;
        return;
    }
    Stack tmp;
    int datatmp, sized = s.size;
    for (int i = 1; i <= sized; i++)
    {
        datatmp = s.pop();
        tmp.push(datatmp);
    }
    for (int i = 1; i <= sized; i++)
    {
        datatmp = tmp.pop();
        s.push(datatmp);
        cout << "№" << i << ". " << datatmp << endl;
    }
}
void delElems(Stack& s, int n, int k)
{
    if (s.size == 0)
    {
        cout << "Стек пуст." << endl;
        return;
    }
    if ((n + k - 1) > s.size)
    {
        cout << "Проверьте правильность введенных данных" << endl;
        return;
    }
    Stack tmp;
    int datatmp, carry = (s.size - n - k +1);
    for (int i = 1; i <= carry; i++)
    {
        datatmp = s.pop();
        tmp.push(datatmp);
    }
    for (int i = 1; i <= k; i++) s.pop();
    for (int i = 1; i <= carry; i++)
    {
        datatmp = tmp.pop();
        s.push(datatmp);
    }
}
void adder(Stack& s, int n, int data)
{
    if (s.size == 0)
    {
        cout << "Невозможно, так как стек пуст." << endl;
        return;
    }
    if (n > s.size)
    {
        cout << "Проверьте правильность введенных данных" << endl;
        return;
    }
    Stack tmp;
    int datatmp, carry = (s.size - n + 1);
    for (int i = 1; i <= carry; i++)
    {
        datatmp = s.pop();
        tmp.push(datatmp);
    }
    s.push(data);
    for (int i = 1; i <= carry; i++)
    {
        datatmp = tmp.pop();
        s.push(datatmp);
    }
}
void killer(Stack& s)
{
    int sized = s.size;
    for (int i = 1; i <= sized; i++) s.pop();
}
void saver(Stack& s)
{
    FILE* f;
    if ((f = fopen("file.bin", "wb")) == NULL) exit(1);
    fwrite(&s.size, sizeof(int), 1, f);
    Stack tmp;
    int datatmp, sized = s.size;
    for (int i = 1; i <= sized; i++)
    {
        datatmp = s.pop();
        tmp.push(datatmp);
    }
    for (int i = 1; i <= sized; i++)
    {
        datatmp = tmp.pop();
        fwrite(&datatmp, sizeof(int), 1, f);
        s.push(datatmp);
    }
    fclose(f);
}
void uploader(Stack& s)
{
    int sizzz, datatmp;
    FILE* f;
    if ((f = fopen("file.bin", "rb")) == NULL) exit(2);
    fread(&sizzz, sizeof(int), 1, f);
    for (int i = 1; i <= sizzz; i++)
    {
        fread(&datatmp, sizeof(int), 1, f);
        s.push(datatmp);
    }
    fclose(f);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    Stack stec;
    int n, k;
    cout << "Введите размер стека ";
    cin >> n;
    createStack(stec, n);
    printStack(stec);
    cout << "Введите номер элемента в стеке и количество элементов для удаления (элементы удаляются с заданного включительно) ";
    cin >> n;
    cin >> k;
    delElems(stec, n, k);
    printStack(stec);
    cout << "Введите номер элемента в стеке перед которым нужно вставить ещё один, и значение вставляемого элемента  ";
    cin >> n;
    cin >> k;
    adder(stec, n, k);
    printStack(stec);
    saver(stec);
    killer(stec);
    printStack(stec);
    uploader(stec);
    printStack(stec);
    killer(stec);
    printStack(stec);
    return 0;
}
/*
        ТЕСТЫ
1) Консоль:
Введите размер стека 5
Введите элемент стека 12
Введите элемент стека -876
Введите элемент стека 0
Введите элемент стека 12
Введите элемент стека 555
№1. 12
№2. -876
№3. 0
№4. 12
№5. 555
Введите номер элемента в стеке и количество элементов для удаления (элементы удаляются с заданного включительно) 1 2
№1. 0
№2. 12
№3. 555
Введите номер элемента в стеке перед которым нужно вставить ещё один, и значение вставляемого элемента  1 -1
№1. -1
№2. 0
№3. 12
№4. 555
Стек пуст.
№1. -1
№2. 0
№3. 12
№4. 555
Стек пуст.


2) Консоль:
Введите размер стека 6
Введите элемент стека 123
Введите элемент стека 987
Введите элемент стека 267
Введите элемент стека 8
Введите элемент стека -654
Введите элемент стека 222222
№1. 123
№2. 987
№3. 267
№4. 8
№5. -654
№6. 222222
Введите номер элемента в стеке и количество элементов для удаления (элементы удаляются с заданного включительно) 4 3
№1. 123
№2. 987
№3. 267
Введите номер элемента в стеке перед которым нужно вставить ещё один, и значение вставляемого элемента  3 33333
№1. 123
№2. 987
№3. 33333
№4. 267
Стек пуст.
№1. 123
№2. 987
№3. 33333
№4. 267
Стек пуст.


3) Консоль
Введите размер стека 7
Введите элемент стека 12
Введите элемент стека 0
Введите элемент стека 0
Введите элемент стека 6666
Введите элемент стека -643
Введите элемент стека 98
Введите элемент стека 34
№1. 12
№2. 0
№3. 0
№4. 6666
№5. -643
№6. 98
№7. 34
Введите номер элемента в стеке и количество элементов для удаления (элементы удаляются с заданного включительно) 2 2
№1. 12
№2. 6666
№3. -643
№4. 98
№5. 34
Введите номер элемента в стеке перед которым нужно вставить ещё один, и значение вставляемого элемента  4 6666
№1. 12
№2. 6666
№3. -643
№4. 6666
№5. 98
№6. 34
Стек пуст.
№1. 12
№2. 6666
№3. -643
№4. 6666
№5. 98
№6. 34
Стек пуст.
*/