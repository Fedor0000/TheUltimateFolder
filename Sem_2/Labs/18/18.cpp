/*
        Задание
1.	Создать динамический массив из записей (в соответствии с вариантом), содержащий не менее 100 элементов. Для заполнения элементов массива использовать ДСЧ.
2.	Предусмотреть сохранение массива в файл и загрузку массива из файла.
3.	Предусмотреть возможность добавления и удаления элементов из массива (файла).
4.	Выполнить поиск элемента в массиве по ключу в соответствии с вариантом. Для поиска использовать хэш-таблицу.
5.	Подсчитать количество коллизий при размере хэш-таблицы 40, 75 и 90 элементов.

        Методические указания
1. Для выбора действий использовать меню.
2. Для добавления элементов в файл использовать вспомогательную структуру для хранения элементов в оперативной памяти (список). Добавление должно осуществляться в начало, в конец файла и на позицию с заданным номером.
3. Удаление должно осуществляться по ключевому полю и по номеру. Удаляемые из файла записи помечаются как удаленные, когда их количество превысит половину файла, их можно удалять. При удалении использовать вспомогательную структуру для хранения элементов в оперативной памяти (список).
4. Предусмотреть возможность отмены последней операции удаления.
5. Корректировка выполняется по ключу и по номеру.
6. Предусмотреть команду «Сохранить изменения», по которой измененные данные из списка переписываются в файл.
*/
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
using namespace std;
int M;
const double A = M_PI_4;
int collisionCounter = 0;
struct Node
{
    string key;
    string value;
    Node* next = nullptr;
    Node* prev = nullptr;
};
struct HashTable
{
    Node** table = new Node*[M];
    HashTable()
    {
        for (int i = 0; i < M; i++)
        {
            table[i] = nullptr;
        }
    }
};
struct elemMas
{
    string key;
    string value;
};
struct HashMas
{
    elemMas** table = new elemMas*[M];
    HashMas()
    {
        for (int i = 0; i < M; i++)
        {
            table[i] = nullptr;
        }
    }
};
double mod1(double k)
{
    int intPart = static_cast<int>(k);
    return k - intPart;
}
int getHash(double k)
{
    return static_cast<int>(M * mod1(k * A));
}
int getHash(string line)
{
    int n = 0;
    for (int i = 0; i < line.size(); i++)
    {
        n += static_cast<int>(pow(line[i], 2) + M_2_SQRTPI + abs(line[i]) + M_SQRT1_2);
    }
    return getHash(abs(n));
}
bool add(HashTable& table, string key, string elem)
{
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = elem;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    int hash = getHash(key);
    if (table.table[hash] == nullptr)
    {
        table.table[hash] = newNode;
        return true;
    }
    else
    {
        Node* current = table.table[hash];
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
        collisionCounter++;
        return true;
    }
}
bool addMas(HashMas& mas, string key, string elem)
{
    int hash = getHash(key);
    elemMas* mass = new elemMas;
    mass->key = key;
    mass->value = elem;
    if (mas.table[hash] == nullptr)
    {
        mas.table[hash] = mass;
        return true;
    }
    else
    {
        while (mas.table[hash] != nullptr)
        {
            if (hash == M - 1) hash = 0;
            else hash++;
        }
        mas.table[hash] = mass;
        collisionCounter++;
        return true;
    }
}
bool removeByKey(HashTable& table, string key)
{
    int hash = getHash(key);
    Node* current = table.table[hash];
    while (current != nullptr)
    {
        if (current->key == key)
        {
            if (current->prev != nullptr)
            {
                current->prev->next = current->next;
            }
            else
            {
                table.table[hash] = current->next;
            }
            if (current->next != nullptr)
            {
                current->next->prev = current->prev;
            }
            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}
bool removeByKeyMas(HashMas& mas, string key)
{
    int hash = getHash(key);
    for (int i = 0; i < M; i++)
    {
        if (mas.table[hash] == nullptr)
        {
            if (hash == M - 1)
            {
                hash = 0;
            }
            else hash++;
        }
        else if (mas.table[hash]->key == key)
        {
            elemMas* current = mas.table[hash];
            mas.table[hash] = nullptr;
            delete current;
            return true;
        }
        else if (hash == M - 1)
        {
            hash = 0;
        }
        else hash++;
    }
    return false;
}
bool removeByValue(HashTable& table, string elem)
{
    for (int i = 0; i < M; i++)
    {
        Node* current = table.table[i];
        while (current != nullptr)
        {
            if (current->value == elem)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    table.table[i] = current->next;
                }
                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                delete current;
                return true;
            }
            current = current->next;
        }
    }
    return false;
}
bool removeByValueMas(HashMas& mas, string elem)
{
    for (int i = 0; i < M; i++)
    {
        if (mas.table[i] == nullptr) continue;
        if (mas.table[i]->value == elem)
        {
            elemMas* current = mas.table[i];
            mas.table[i] = nullptr;
            delete current;
            return true;
        }
    }
    return false;
}
Node* get(HashTable& table, string key)
{
    int hash = getHash(key);
    Node* current = table.table[hash];
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
elemMas* getMas(HashMas& mas, string key)
{
    int hash = getHash(key);
    for (int i = 0; i < M; i++)
    {
        if (mas.table[hash] == nullptr)
        {
            if (hash == M - 1)
            {
                hash = 0;
            }
            else hash++;
        }
        else if (mas.table[hash]->key == key)
        {
            elemMas* current = mas.table[hash];
            return current;
        }
        else if (hash == M - 1)
        {
            hash = 0;
        }
        else hash++;
    }
    return nullptr;
}
void print(HashTable table)
{
    for (int i = 0; i < M; i++)
    {
        Node* current = table.table[i];
        while (current != nullptr)
        {
            std::cout << "[" << current->key << ": " << current->value << "]\n";
            current = current->next;
        }
    }
    std::cout << endl;
}
void printMas(HashMas mas)
{
    for (int i = 0; i < M; i++)
    {
        elemMas* current = mas.table[i];
        if (current != nullptr)
        {
            std::cout << "[" << current->key << ": " << current->value << "]\n";
        }
    }
    std::cout << endl;
}
string surnames[] =
{
    "Иванов", "Смирнов", "Кузнецов", "Попов", "Соколов", "Лебедев", "Козлов", "Новиков", "Морозов", "Петров", "Волков", "Соловьёв", "Васильев", "Зайцев", "Павлов", "Семёнов", "Голубев", "Виноградов", "Богданов", "Воробьёв", "Фёдоров", "Михайлов", "Беляев", "Тарасов", "Белов", "Жуланов", "Орлов", "Киселёв", "Макаров", "Андреев"
};
string names[] =
{
    "Александр", "Сергей", "Андрей", "Дмитрий", "Алексей", "Михаил", "Иван", "Евгений", "Анатолий", "Владимир", "Николай", "Юрий", "Виктор", "Олег", "Константин", "Валенитин", "Валерий", "Вадим", "Афанасий", "Станислав", "Роман", "Игорь", "Геннадий", "Вячеслав", "Давид", "Никита", "Артём", "Тимур", "Руслан", "Семён"
};
string patronymics[] =
{
    "Александрович", "Сергеевич", "Андреевич", "Дмитриевич", "Алексеевич", "Иванович", "Николаевич", "Михайлович", "Олегович", "Петрович", "Анатольевич", "Владимирович", "Юрьевич","Викторович", "Фёдорович", "Константинович", "Аркадьевич", "Егорович", "Васильевич", "Тимофеевич", "Игоревич", "Валерьевич", "Станиславович", "Романович", "Геннадьевич", "Павлович", "Вячеславович", "Евгеньевич", "Давыдович", "Григорьевич"
};
string generateFullName()
{
    return surnames[rand() % 30] + ' ' + names[rand() % 30] + ' ' + patronymics[rand() % 30];
};
string correctStr(int n, int length)
{
    string strn = to_string(n);
    while (strn.size() < length)
    {
        strn = '0' + strn;
    }
    while (strn.size() > length)
    {
        strn.erase(0, 1);
    }
    return strn;
}
string generateBirthday()
{
    return correctStr(rand() % 28 + 1, 2) + '.' + correctStr(rand() % 12 + 1, 2) + '.' + to_string(rand() % 74 + 1950);
}
string generatePassportNum()
{
    return correctStr(rand() % 10000, 4) + ' ' + correctStr((rand() % 1000000 + 100 + rand()), 6);
}
HashTable createHashTableWithList()
{
    std::cout << "Введите размер Hash-таблицы: ";
    std::cin >> M;
    while (M < 1)
    {
        std::cout << "Введите корректный размер Hash-таблицы. ";
        std::cin >> M;
    }
    int kol;
    std::cout << "Введите количество записей Hash-таблицы: ";
    std::cin >> kol;
    while (kol < 1)
    {
        std::cout << "Введите корректное количество записей Hash-таблицы. ";
        std::cin >> kol;
    }
    std::cout << std::endl;
    HashTable myTable;
    for (int i = 0; i < kol; i++)
    {
        string birthDay = generateBirthday();
        string newHuman = generateFullName() + " | " + birthDay + " | " + generatePassportNum();
        add(myTable, birthDay, newHuman);
    }
    std::cout << "Создана хэш-таблица: " << endl;
    print(myTable);
    return myTable;
}
void removeByKey(HashTable& t)
{
    string keyToRemove;
    std::cout << "Введите ключ, по которому будет удален элемент ";
    getline(cin, keyToRemove);
    getline(cin, keyToRemove); // как обычно для очистки буфера
    std::cout << "Удаление по ключу '" << keyToRemove << "':" << endl;
    if (removeByKey(t, keyToRemove))
    {
        std::cout << "Элемент с ключом '" << keyToRemove << "' успешно удалён." << endl;
    }
    else
    {
        std::cout << "Элемент с ключом '" << keyToRemove << "' не найден." << endl;
    }
    print(t);
}
void removeByValue(HashTable& t)
{
    string valueToRemove;
    std::cout << "Введите значение, по которому будет удален элемент ";
    getline(cin, valueToRemove);
    std::cout << "Удаление по значению '" << valueToRemove << "':" << endl;
    if (removeByValue(t, valueToRemove))
    {
        cout << "Элемент со значением '" << valueToRemove << "' успешно удалён." << endl;
    }
    else
    {
        cout << "Элемент со значением '" << valueToRemove << "' не найден." << endl;
    }
    print(t);
}
void get(HashTable& t)
{
    string keyToGet;
    std::cout << "Введите ключ по которому будет найден элемент ";
    getline(cin, keyToGet);
    cout << "Получение элемента по ключу '" << keyToGet << "':" << endl;
    Node* node = get(t, keyToGet);
    if (node != nullptr)
    {
        cout << "Найден элемент: " << node->value << endl;
    }
    else
    {
        cout << "Элемент с ключом '" << keyToGet << "' не найден." << endl;
    }
}
HashMas createHashTableWithMas()
{
    std::cout << "Введите размер Hash-таблицы: ";
    std::cin >> M;
    while (M < 1)
    {
        std::cout << "Введите корректный размер Hash-таблицы. ";
        std::cin >> M;
    }
    int kol;
    std::cout << "Введите количество записей Hash-таблицы: ";
    std::cin >> kol;
    while ((kol < 1) || (kol > M))
    {
        std::cout << "Введите корректное количество записей Hash-таблицы (не более размера hash-таблицы). ";
        std::cin >> kol;
    }
    std::cout << std::endl;
    HashMas myTable;
    for (int i = 0; i < kol; i++)
    {
        string birthDay = generateBirthday();
        string newHuman = generateFullName() + " | " + birthDay + " | " + generatePassportNum();
        addMas(myTable, birthDay, newHuman);
    }
    std::cout << "Создана хэш-таблица: " << endl;
    printMas(myTable);
    return myTable;
}
void removeByKeyMas(HashMas& t)
{
    string keyToRemove;
    std::cout << "Введите ключ, по которому будет удален элемент ";
    getline(cin, keyToRemove);
    getline(cin, keyToRemove); // как обычно для очистки буфера
    std::cout << "Удаление по ключу '" << keyToRemove << "':" << endl;
    if (removeByKeyMas(t, keyToRemove))
    {
        std::cout << "Элемент с ключом '" << keyToRemove << "' успешно удалён." << endl;
    }
    else
    {
        std::cout << "Элемент с ключом '" << keyToRemove << "' не найден." << endl;
    }
    printMas(t);
}
void removeByValueMas(HashMas& t)
{
    string valueToRemove;
    std::cout << "Введите значение, по которому будет удален элемент ";
    getline(cin, valueToRemove);
    std::cout << "Удаление по значению '" << valueToRemove << "':" << endl;
    if (removeByValueMas(t, valueToRemove))
    {
        cout << "Элемент со значением '" << valueToRemove << "' успешно удалён." << endl;
    }
    else
    {
        cout << "Элемент со значением '" << valueToRemove << "' не найден." << endl;
    }
    printMas(t);
}
void getMas(HashMas& t)
{
    string keyToGet;
    std::cout << "Введите ключ по которому будет найден элемент ";
    getline(cin, keyToGet);
    cout << "Получение элемента по ключу '" << keyToGet << "':" << endl;
    elemMas* node = getMas(t, keyToGet);
    if (node != nullptr)
    {
        cout << "Найден элемент: " << node->value << endl;
    }
    else
    {
        cout << "Элемент с ключом '" << keyToGet << "' не найден." << endl;
    }
}
void mainMenu()
{
    int method;
    std::cout << "Выберите режим Hash-таблицы:\n0. Выход из программы.\n1. Сдвиг одинакого хэша вперед по циклу.\n2. Одинаковые хэши - элементы списка.\nВыбранный способ -> ";
    std::cin >> method;
    switch (method)
    {
    default:
    {
        std::cout << "Введите существующий пункт меню!" << endl;
        mainMenu();
        break;
    }
    case 0:
    {
        std::cout << "До скорых встреч!" << endl;
        break;
    }
    case 1:
    {
        std::cout << "Выбрано: Сдвиг одинакого хэша вперед по циклу." << endl;
        HashMas hashMas = createHashTableWithMas();
        removeByKeyMas(hashMas);
        removeByValueMas(hashMas);
        getMas(hashMas);
        cout << "Число коллизий: " << collisionCounter << endl;
        collisionCounter = 0;
        mainMenu();
        break;
    }
    case 2:
    {
        std::cout << "Выбрано: Одинаковый хэш - элементы списка." << endl;
        HashTable hashTable = createHashTableWithList();
        removeByKey(hashTable);
        removeByValue(hashTable);
        get(hashTable);
        cout << "Число коллизий: " << collisionCounter << endl;
        collisionCounter = 0;
        mainMenu();
        break;
    }
    }
}
int main()
{
    system("chcp 1251 > null");
    srand(time(NULL));
    mainMenu();
    return 0;
}