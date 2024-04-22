# Лабораторная работа №8 "Программа, управляемая событиями."

## Постановка задачи

1. Определить иерархию пользовательских классов (см. лабораторную работу №5). Во главе иерархии должен стоять абстрактный класс с чисто виртуальными методами для ввода и вывода информации об атрибутах объектов.
2. Реализовать конструкторы, деструктор, операцию присваивания, селекторы и модификаторы.
3. Определить класс-группу на основе структуры, указанной в варианте.
4. Для группы реализовать конструкторы, деструктор, методы для добавления и удаления элементов в группу, метод для просмотра группы, перегрузить операцию для получения информации о размере группы.
5. Определить класс Диалог – наследника группы, в котором реализовать методы для обработки событий.
6. Добавить методы для обработки событий группой и объектами пользовательских классов.
7. Написать тестирующую программу.
8. Нарисовать диаграмму классов и диаграмму объектов.

### 7 Вариант:

Базовый класс:
- ЧЕЛОВЕК (Person)
- Имя – string
- Возраст – int

Производный класс:
- СОТРУДНИК (Emloyee)
- Заработная плата – double
- Должность - string
- Группа – Вектор (Vector).

Команды:
- Создать группу (формат команды: m количество элементов группы).
- Добавить элемент в группу (формат команды: +).
- Удалить элемент из группы (формат команды -).
- Вывести информацию об элементах группы (формат команды: s).
- Вывести информацию об имени элемента с номером k (формат команды : zk, где k целое число).
- Конец работы (формат команды: q).

## UML-диаграмма

![uml](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab8/uml.png)

## Диаграмма объектов

![object](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab8/8.png)

## Код программы

`multilineComment.txt`
```txt
1. Определить иерархию пользовательских классов (см. лабораторную работу №5).
Во главе иерархии должен стоять абстрактный класс с чисто виртуальными
методами для ввода и вывода информации об атрибутах объектов.
2. Реализовать конструкторы, деструктор, операцию присваивания, селекторы и
модификаторы.
3. Определить класс-группу на основе структуры, указанной в варианте.
4. Для группы реализовать конструкторы, деструктор, методы для добавления и
удаления элементов в группу, метод для просмотра группы, перегрузить операцию
для получения информации о размере группы.
5. Определить класс Диалог – наследника группы, в котором реализовать методы для
обработки событий.
6. Добавить методы для обработки событий группой и объектами пользовательских
классов.
7. Написать тестирующую программу.
8. Нарисовать диаграмму классов и диаграмму объектов.


Базовый класс:
ЧЕЛОВЕК (Person)
Имя – string
Возраст – int

Производный класс:
СОТРУДНИК (Emloyee)
Заработная плата – double
Должность - string
Группа – Вектор (Vector).

Команды:
- Создать группу (формат команды: m количество элементов группы).
- Добавить элемент в группу (формат команды: +)
- Удалить элемент из группы (формат команды -)
- Вывести информацию об элементах группы (формат команды: s)
- Вывести информацию об имени элемента с номером k (формат команды : zk, где k целое число)
- Конец работы (формат команды: q)
```

`object.h`
```cpp
#pragma once
#include "event.h"
using namespace std;
class Object
{
public:
	Object();
	virtual void Show() = 0;
	virtual void Input() = 0;
	virtual void HandleEvent(const TEvent& e) = 0;
	virtual ~Object();
};
```

`object.cpp`
```cpp
#pragma once
#include "object.h"
using namespace std;
Object::Object() {}
Object::~Object() {}
```

`person.h`
```cpp
#pragma once
#include "object.h"
#include "event.h"
using namespace std;
class Person :	public Object
{
public:
	Person();
	virtual ~Person();
	void Show();
	void Input();
	Person(string, int);
	Person(const Person&);
	string getName() {return name;}
	int getAge() {return age;}
	void setName(string);
	void setAge(int);
	Person& operator=(const Person&);
	virtual void HandleEvent(const TEvent& e);
protected:
	string name;
	int age;
};
```

`person.cpp`
```cpp
#pragma once
#include <iostream>
#include <string>
#include "person.h"
#include "event.h"
using namespace std;
Person::Person()
{
	name = "";
	age = 0;
}
Person::~Person() {}
Person::Person(string N, int A)
{
	name = N;
	age = A;
}
Person::Person(const Person& person)
{
	name = person.name;
	age = person.age;
}
void Person::setName(string N)
{
	name = N;
}
void Person::setAge(int A)
{
	age = A;
}
Person& Person::operator=(const Person& p)
{
	if (&p == this) return *this;
	name = p.name;
	age = p.age;
	return *this;
}
void Person::HandleEvent(const TEvent& e)
{
	if (e.what == evMessage) //событие-сообщение
	{
		switch (e.command)
		{
		case cmNames: cout << "Имя = " << getName() << endl; break;
		}
	}
}
void Person::Show()
{
	cout << "\nИмя: " << name;
	cout << "\nВозраст: " << age;
	cout << "\n";
}
void Person::Input()
{
	cout << "\nВведите имя: "; cin >> name;
	cout << "\nВведите возраст: "; cin >> age;
}
```

`employee.h`
```cpp
#pragma once
#include "person.h"
using namespace std;
class Employee : public Person
{
public:
	Employee();
	~Employee();
	void Show();
	void Input();
	Employee(string, int, double, string);
	Employee(const Employee&);
	double getSalary() {return salary;}
	string getPositionAtWork() {return positionAtWork;}
	void setSalary(double);
	void setPositionAtWork(string);
	Employee& operator=(const Employee&);
protected:
	double salary;
	string positionAtWork;
};
```

`employee.cpp`
```cpp
#pragma once
#include <iostream>
#include <string>
#include "employee.h"
using namespace std;
Employee::Employee() : Person()
{
	salary = 0;
	positionAtWork = "";
}
Employee::~Employee() {}
Employee::Employee(string N, int A, double S, string P) : Person(N, A)
{
	salary = S;
	positionAtWork = P;
}
Employee::Employee(const Employee& E)
{
	name = E.name;
	age = E.age;
	salary = E.salary;
	positionAtWork = E.positionAtWork;
}
void Employee::setSalary(double S)
{
	salary = S;
}
void Employee::setPositionAtWork(string P)
{
	positionAtWork = P;
}
Employee& Employee::operator=(const Employee& E)
{
	if (&E == this) return *this;
	name = E.name;
	age = E.age;
	salary = E.salary;
	positionAtWork = E.positionAtWork;
	return *this;
}
void Employee::Show()
{
	cout << "\nИмя: " << name;
	cout << "\nВозраст: " << age;
	cout << "\nЗаработная плата: " << salary;
	cout << "\nДолжность: " << positionAtWork;
	cout << "\n";
}
void Employee::Input()
{
	cout << "\nВведите имя: "; cin >> name;
	cout << "\nВведите возраст: "; cin >> age;
	cout << "\nВведите заработную плату: "; cin >> salary;
	cout << "\nВведите должность: "; cin >> positionAtWork;
}
```

`vector.h`
```cpp
#pragma once
#include "event.h"
#include "object.h"
class Vector
{
public:
	Vector();
	Vector(int);
	~Vector();
	void Add();
	void Del();
	void Show();
	int operator()();
	virtual void HandleEvent(const TEvent& e);
protected:
	Object** beg;
	int size;
	int cur;
};
```

`vector.cpp`
```cpp
#pragma once
#include <iostream>
#include <string>
#include "object.h"
#include "vector.h"
#include "person.h"
#include "employee.h"
using namespace std;
Vector::Vector()
{
	beg = nullptr;
	size = 0;
	cur = 0;
}
Vector::~Vector()
{
	if (beg != 0)delete[] beg;
	beg = 0;
}
Vector::Vector(int n)
{
	beg = new Object * [n];
	cur = 0;
	size = n;
}
void Vector::Add()
{
	Object* p;
	cout << "1. Человек" << endl;
	cout << "2. Сотрудник" << endl;
	int y;
	cin >> y;
	if (y == 1)
	{
		Person* a = new Person;
		a->Input();
		p = a;
		if (cur < size)
		{
			beg[cur] = p;
			cur++;
		}
	}
	else if (y == 2)
	{
		Employee* b = new Employee;
		b->Input();
		p = b;
		if (cur < size)
		{
			beg[cur] = p;
			cur++;
		}
	}
	else return;
}
void Vector::Show()
{
	if (cur == 0) cout << "Пусто" << endl;
	Object** p = beg;
	for (int i = 0; i < cur; i++)
	{
		(*p)->Show();
		p++;
	}
}
int Vector::operator ()()
{
	return cur;
}
void Vector::HandleEvent(const TEvent& e)
{
	if (e.what == evMessage)
	{
		Object** p = beg;
		for (int i = 0; i < cur; i++)
		{
			(*p)->HandleEvent(e);
			p++;
		}
	}
}
void Vector::Del()
{
	if (cur == 0) return;
	cur--;
}
```

`event.h`
```cpp
#pragma once
const int evNothing = 0; //пустое событие
const int evMessage = 100; //непустое событие
const int cmAdd = 1; //добавить объект в группу
const int cmDel = 2; //удалить объект из группы
const int cmNames = 3; //вывести атрибут всех объектов
const int cmShow = 4; //вывести всю группу
const int cmOneName = 5; // одно имя
const int cmMake = 6; //создать группу
const int cmQuit = 101; //выход
struct TEvent
{
	int what;
	union
	{
		int command;
		struct
		{
			int message;
			int a;
		};
	};
};
```

`dialog.h`
```cpp
#pragma once
#include "event.h"
#include "vector.h"
class Dialog : public Vector
{
public:
	Dialog();
	virtual ~Dialog();
	virtual void GetEvent(TEvent& event);
	virtual int Execute();
	virtual void HandleEvent(TEvent& event);
	virtual void ClearEvent(TEvent& event);
	int Valid();
	void EndExec();
protected:
	int EndState;
};
```

`dialog.cpp`
```cpp
#pragma once
#include <iostream>
#include <string>
#include "dialog.h"
#include "event.h"
#include "vector.h"
#include "object.h"
using namespace std;
Dialog::Dialog() : Vector() {EndState = 0;}
Dialog::~Dialog() {}
void Dialog::GetEvent(TEvent& event)
{
	string OpInt = "+-s/qmz";
	string str;
	string param;
	char code;
	cout << '>';
	cin >> str; code = str[0];
	if (OpInt.find(code) < INT64_MAX) // так как str.find(string) выводит UINT64_MAX, если не находит подстроку, а UINT64_MAX > INT64_MAX
	{
		event.what = evMessage;
		switch (code)
		{
		case 'm': event.command = cmMake;     break; //создать группу
		case '+': event.command = cmAdd;      break; //добавить объект в группу
		case '-': event.command = cmDel;      break; //удалить объект из группы
		case 's': event.command = cmShow;     break; //просмотр группы
		case 'q': event.command = cmQuit;     break; //конец работы
		case '/': event.command = cmNames;    break; // вывести все имена
		case 'z': event.command = cmOneName;  break; // вывести все имена
		}
		if (str.length() > 1)
		{
			param = str.substr(1, str.length() - 1);
			int A = atoi(param.c_str());
			event.a = A;
		}
	}
	else event.what = evNothing;
}
int Dialog::Execute()
{
	TEvent event;
	do
	{
		EndState = 0;
		GetEvent(event); //получить событие
		HandleEvent(event); //обработать событие
	}
	while (!Valid());
	return EndState;
}
int Dialog::Valid()
{
	if (EndState == 0) return 0;
	else return 1;
}
void Dialog::ClearEvent(TEvent& event)
{
	event.what = evNothing;//пустое событие
}
void Dialog::EndExec()
{
	EndState = 1;
}
void Dialog::HandleEvent(TEvent& event)
{
	if (event.what == evMessage)
	{
		switch (event.command)
		{
		case cmMake: //создание группы
		{
			size = event.a; //размер группы
			if (event.a <= 0)
			{
				cout << "Введен неадекватный размер!" << endl;
				break;
			}
			beg = new Object * [size];
			cur = 0;
			ClearEvent(event);
			break;
		}
		case cmAdd://добавление
		{
			Add();
			ClearEvent(event);
			break;
		}
		case cmDel: //удаление
		{
			Del();
			ClearEvent(event);
			break;
		}
		case cmShow: //просмотр
		{
			Show();
			ClearEvent(event);
			break;
		}
		case cmQuit: //выход
		{
			EndExec();
			ClearEvent(event);
			break;
		}
		case cmNames: // вывод имен
		{
			Vector::HandleEvent(event);
			ClearEvent(event);
			break;
		}
		case cmOneName: // вывод имени по номеру
		{
			if ((event.a > cur)||(event.a <=0))
			{
				cout << "Введен неадекватный номер!" << endl;
				break;
			}
			Object** p = beg;
			for (int i = 0; i < event.a-1; i++) p++;
			cout << "Имя элемента с номером " << event.a << endl;
			TEvent e;
			e.what = evMessage;
			e.command = cmNames;
			(*p)->HandleEvent(e);
			ClearEvent(event);
			break;
		}
		default:
		{
			ClearEvent(event);
			break;
		}
		}
	};
}
```

`main.cpp`
```cpp
#include <iostream>
#include <string>
#include "dialog.h"
#include "event.h"
#include "vector.h"
#include "object.h"
int main()
{
	system("chcp 1251 > null");
	Dialog D;
	D.Execute();
	return 0;
}
}
```

## Тесты текстом

```txt
1)
>m3
>+
1. Человек
2. Сотрудник
1

Введите имя: Василий

Введите возраст: 34
>+
1. Человек
2. Сотрудник
2

Введите имя: Кассир

Введите возраст: 56

Введите заработную плату: 0.56

Введите должность: Кассир
>+
1. Человек
2. Сотрудник
1

Введите имя: Питя

Введите возраст: 34
>ы
>s

Имя: Василий
Возраст: 34

Имя: Кассир
Возраст: 56
Заработная плата: 0.56
Должность: Кассир

Имя: Питя
Возраст: 34
>-
>s

Имя: Василий
Возраст: 34

Имя: Кассир
Возраст: 56
Заработная плата: 0.56
Должность: Кассир
>+
1. Человек
2. Сотрудник
1

Введите имя: Петя

Введите возраст: 34
>z3
Имя элемента с номером 3
Имя = Петя
>z1
Имя элемента с номером 1
Имя = Василий
>/
Имя = Василий
Имя = Кассир
Имя = Петя
>q


2)
>Что?
>+
1. Человек
2. Сотрудник
1

Введите имя: Нерабочий

Введите возраст: 0
>ы
>s
Пусто
>m-6
Введен неадекватный размер!
>m0
Введен неадекватный размер!
>m1
>+
1. Человек
2. Сотрудник
2

Введите имя: Человек

Введите возраст: 23

Введите заработную плату: 23.23

Введите должность: Адекватный
>ы
>s

Имя: Человек
Возраст: 23
Заработная плата: 23.23
Должность: Адекватный
>z-3
Введен неадекватный номер!
>z0
Введен неадекватный номер!
>z2
Введен неадекватный номер!
>z1
Имя элемента с номером 1
Имя = Человек
>q


3)
>m2
>/
>s
Пусто
>z1
Введен неадекватный номер!
>z0
Введен неадекватный номер!
>z2
Введен неадекватный номер!
>z-1
Введен неадекватный номер!
>+
1. Человек
2. Сотрудник
2

Введите имя: Клоун

Введите возраст: 23

Введите заработную плату: 87790.09

Введите должность: Старший
>+
1. Человек
2. Сотрудник
1

Введите имя: поосоп

Введите возраст: 398
>-
>+
1. Человек
2. Сотрудник
1

Введите имя: Политик

Введите возраст: 39
>ы
>s

Имя: Клоун
Возраст: 23
Заработная плата: 87790.09
Должность: Старший

Имя: Политик
Возраст: 39
>q
```

## Тесты скриншоты

![Скриншот номер 1](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab8/screen/1.png)
![Скриншот номер 2](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab8/screen/2.png)
![Скриншот номер 3](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab8/screen/3.png)

## Ответы на вопросы

**1. Что такое класс-группа? Привести примеры таких классов.**

`Класс-группа (или группа классов) представляет собой совокупность связанных классов, которые имеют общие характеристики или наследуются от одного базового класса. Это позволяет организовать иерархию классов для более удобного управления и структурирования кода.`
`Примеры классов-групп:`
`Геометрические фигуры: Классы Circle, Rectangle, Triangle могут быть частью группы, так как они имеют общие свойства (например, площадь, периметр).`
`Список (List): В группе классов для работы со списками могут быть классы Node, LinkedList, DoubleLinkedList, ArrayList, которые реализуют разные способы хранения и управления данными в списках.`

**2. Привести пример описания класса-группы Список (List).**

```cpp
class List
{
public:
    List(); // Конструктор по умолчанию
    List(const List& other); // Конструктор копирования
    ~List(); // Деструктор
    void add(int value); // Метод добавления элемента
    bool isEmpty() const; // Метод проверки на пустоту
    void print() const; // Метод для просмотра элементов
private:
    struct Node
	{
        int data;
        Node* next;
        Node(int data, Node* next = nullptr) : data(data), next(next) {}
    };
    Node* head; // Указатель на начало списка
};
```

**3. Привести пример конструктора (с параметром, без параметров, копирования) для класса-группы Список.**

```cpp
// Конструктор без параметров
List::List() : head(nullptr) {}

// Конструктор с параметром
List::List(int initialValue)
{
    head = new Node(initialValue);
}

// Конструктор копирования
List::List(const List& other) : head(nullptr)
{
    Node* current = other.head;
    while (current != nullptr)
	{
        add(current->data);
        current = current->next;
    }
}
```

**4. Привести пример деструктора для класса-группы Список.**

```cpp
List::~List()
{
    Node* current = head;
    while (current != nullptr)
	{
        Node* next = current->next;
        delete current;
        current = next;
    }
}
```

**5. Привести пример метода для просмотра элементов для класса-группы Список.**

```cpp
void List::print()
{
    Node* current = head;
    while (current != nullptr)
	{
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
```

**6. Какой вид иерархии дает группа?**

`Группа в объектно-ориентированном программировании может образовывать иерархию, где один класс является базовым (группой), а другие классы наследуют его свойства и методы. Это позволяет организовать объекты в логически связанные группы и обеспечить общие характеристики для всех классов в этой группе.`

**7. Почему во главе иерархии классов, содержащихся в группе объектов должен находиться абстрактный класс?**

`Абстрактный класс служит базовым для других классов в группе. Он определяет общие свойства и методы, которые должны быть унаследованы другими классами. Поскольку абстрактный класс не может быть инстанциирован (т.е. создан как объект), он обеспечивает общий интерфейс для всех классов в группе, но не предоставляет конкретную реализацию.`

**8. Что такое событие? Для чего используются события?**

`Событие в программировании — это сообщение, которое возникает в различных точках исполняемого кода при выполнении определенных условий. События используются для реагирования на действия пользователя или системы, делая программы более интерактивными и отзывчивыми. Например, события могут возникать при клике мышью, нажатии клавиши, изменении размера окна или завершении загрузки веб-страницы.`

**9. Какие характеристики должно иметь событие-сообщение?**

`Событие-сообщение обычно имеет следующие характеристики: уникальный идентификатор события, текстовое сообщение о сути произошедшего, модель событий, которая принимает событие, данные, которые переносятся от одного объекта к другому.`

**10. Привести пример структуры, описывающей событие.**

```cpp
struct Event
{
    int eventId; // Уникальный идентификатор события
    std::string message; // Текстовое сообщение о событии
    .......
	// Дополнительные поля
	.......
};
```
`В этой структуре eventId может быть числовым идентификатором, а message — описанием события. Также могут существовать дополнительные поля в зависимости от конкретных требований.`

**11. Задана структура события**
```cpp
struct TEvent
{
	int what;
	union
	{
		MouseEventType mouse;
		KeyDownEvent keyDown;
		MessageEvent message;
	}
};
```
**Какие значения, и в каких случаях присваиваются полю what?**

`В структуре TEvent, поле what обычно используется для указания типа события. В зависимости от типа события, это поле может принимать различные значения, которые затем используются для определения, какие данные в объединении (union) активны и могут быть безопасно прочитаны. В данном примере:`
`Если what равно значению, указывающему на событие мыши, то активным становится поле mouse.`
`Если what равно значению, указывающему на событие клавиатуры, то активным становится поле keyDown.`
`Если what равно значению, указывающему на сообщение, то активным становится поле message.`

**12. Задана структура события**
```cpp
struct TEvent
{
	int what; // тип события
	union
	{
		int command; // код комманды
		struct // параметры команды
		{
			int message;
			int a;
		};
	};
};
```
**Какие значения, и в каких случаях присваиваются полю command?**

`Поле command во второй структуре TEvent используется для хранения целочисленного кода команды, когда what указывает на командное событие. Это значение может быть использовано для определения действия, которое должно быть выполнено в ответ на событие.`

**13. Задана структура события**
```cpp
struct TEvent
{
	int what; // тип события
	union
	{
		int command; // код комманды
		struct // параметры команды
		{
			int message;
			int a;
		};
	};
};
```
**Для чего используются поля a и message?**

`Поля a и message в структуре TEvent могут использоваться для хранения дополнительных параметров команды. message может содержать идентификатор сообщения, а a — значение, связанное с сообщением или командой.`

**14. Какие методы необходимы для организации обработки сообщений?**

`Методы для получения события, выполнения, отчистки, также может быть создан класс Dialog, который будет иметь другие методы, необходимые для обработки событий.`

**15. Какой вид имеет главный цикл обработки событий-сообщений?**

`Главный цикл работает, пока valid() возвращает true (так как в начале неизвестно, что будет возвращать метод, цикл обычно с постусловием), он запрашивает у пользователя сообщения, обрабатывает их, очищает из памяти, снова спрашивает, и т. д., до тех пор, пока не получит сообщение, при обработке которого valid() перестанет выдавать true, после чего цикл завершается.`

**16. Какую функцию выполняет метод ClearEvent()? Каким образом?**

`Метод ClearEvent() обычно используется для очистки или сброса состояния события, обычно, путем сброса кодов событий и сообщений.`

**17. Какую функцию выполняет метод HandleEvent()? Каким образом?**

`Метод HandleEvent() обычно отвечает за обработку события. В метод передается событие, в котором есть код события, в зависимости от которого выполняются те или иные действия.`

**18. Какую функцию выполняет метод GetEvent()?**

`Этот метод обычно занимается получением события из сообщения, например, выделяет команду из строки и переводит в целочисленный код команды.`

**19. Для чего используется поле EndState? Какой класс (объект) содержит это поле?**

`Обычно это поле указывает на состояние класса Dialog, если оно равно единице, диалог завершается, в зависимости от контекста завершающим состоянием может быть и ноль.`

**20. Для чего используется функция Valid()?**

`Этот метод возвращает true, если необходимо продолжать выполнение основного цикла, а если не надо - то false, работает он путем проверки EndState. Используется в основном цикле класса Dialog в условии выхода.`
