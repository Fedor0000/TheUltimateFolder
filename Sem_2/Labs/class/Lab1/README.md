# Лабораторная работа №1 "Классы и объекты. Инкапсуляция."

## Постановка задачи

1. Реализовать определение нового класса. Для демонстрации работы с объектами написать главную функцию. Продемонстрировать разные способы создания объектов и массивов объектов.
2. Структура - пара - структура с двумя полями, которые обычно имеют имена first и second. Требуется реализовать тип данных с помощью такой структуры.Во всех заданиях должны присутствовать:
	a. метод инициализации Init (метод должен контролировать значения аргументов на корректность);
	b. ввод с клавиатуры Read;
	c. вывод на экран Show.
3. Реализовать внешнюю функцию make тип(), где тип - тип реализуемой структуры.Функция должна получать значения для полей структуры как параметры функции и возвращать структуру как результат. При передаче ошибочых параметров следует выводить сообщение и заканчивать работу.

### 7 Вариант:

Линейное уравнение у=Ax+В. Поле first - дробное число, коэффициент А, поле second - дробное число, коэффициент B. Реализовать метод function(double x) - вычисление значения у для заданного х.

## UML-диаграмма

пока не готова

## Код программы

`equation.h`
```cpp
#pragma once
class equation
{
	bool isNumber(std::string);
public:
	double first;
	double second;
	void Init(double, double);
	void Init(std::string, std::string);
	void Read();
	void Show();
	double Function(double);
};
```

`equation.cpp`
```cpp
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "equation.h"
using namespace std;
bool equation::isNumber(const string str)
{
    double val;
    istringstream iss(str);
    iss >> noskipws >> val;
    return iss.eof() && !iss.fail();
}
void equation::Init(double F, double S)
{
    first = F;
    second = S;
}
void equation::Init(string F, string S)
{
    cout << "According to you " << F << " and " << S << " - is a numbers?";
    exit(1);
}
void equation::Read()
{
    string tmp;
    cout << "Enter number А: ";
    cin >> tmp;
    if (isNumber(tmp))
    {
        first = stod(tmp);
    }
    else
    {
        cout << "According to you " << tmp << " - is a number?";
        exit(1);
    }
    cout << "Enter number B: ";
    cin >> tmp;
    if (isNumber(tmp))
    {
        second = stod(tmp);
    }
    else
    {
        cout << "According to you " << tmp << " - is a number?";
        exit(1);
    }
}
void equation::Show()
{
    cout << "А = " << first;
    cout << "\nB = " << second << endl;
}
double equation::Function(double x)
{
    return (first*x+second);
}
```

`equationsMain.cpp`
```cpp
#include <iostream>
#include "equation.h"
using namespace std;
equation make_equation(double F, double S)
{
	equation t;
	t.Init(F, S);
	return t;
}
int main()
{
	setlocale(LC_ALL, "en_US"); // русский локаль ломает функцию преобразования строк в дабл
	double iks;

	cout << "Regular variable:" << endl;
	equation A;
	equation B;
	A.Init(3.0, 2.2);
	A.Show();
	cout << "y = A * 4 + B = " << A.Function(4) << endl;
	B.Read();
	B.Show();
	cout << "x = ";
	cin >> iks;
	cout << endl << "y = " << B.first << " * " << iks << " + " << B.second << " = " << B.Function(iks) << endl;

	cout << "Dynamical variable:" << endl;
	equation* C = new equation;
	C->Init(2.0, 5);
	C->Show();
	cout << "x = ";
	cin >> iks;
	cout << endl << "y = " << B.first << " * " << iks << " + " << B.second << " = " << B.Function(iks) << endl;
	delete C;

	cout << "Three elemental static array:" << endl;
	equation mas[3];
	double iksMas[3];
	for (int i = 0; i < 3; i++) mas[i].Read();
	for (int i = 0; i < 3; i++) mas[i].Show();
	cout << "Enter x quotients for three equations:" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "x" << i + 1 << " = ";
		cin >> iksMas[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cout << endl << "y = " << mas[i].first << " * " << iksMas[i] << " + " << mas[i].second << " = " << mas[i].Function(iksMas[i]) << endl;
	}

	cout << "N elemental dynamical array:" << endl;
	int N;
	cout << "N = ";
	cin >> N;
	cout << endl;

	equation* p_mas = new equation[N];
	double* iksMasD = new double[N];
	for (int i = 0; i < N; i++) p_mas[i].Read();
	for (int i = 0; i < N; i++) p_mas[i].Show();
	cout << "Enter x quotients for N equations::" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "x" << i + 1 << " = ";
		cin >> iksMasD[i];
	}
	for (int i = 0; i < N; i++)
	{
		cout << endl << "y = " << p_mas[i].first << " * " << iksMasD[i] << " + " << p_mas[i].second << " = " << p_mas[i].Function(iksMasD[i]) << endl;
	}
	delete[] p_mas;
	delete[] iksMasD;

	cout << "Using function make_equation(a, b):" << endl;
	double y; double z;
	cout << "A = ";
	cin >> y;
	cout << "B = ";
	cin >> z;
	equation F = make_equation(y, z);
	cout << "Output:" << endl;
	F.Show();
	return 0;
}
```

## Тесты текстом

```cpp
/*
1)
Regular variable:
A = 3
B = 2.2
y = A * 4 + B = 14.2
Enter number A: 5
Enter number B: 5.5
A = 5
B = 5.5
x = -7.6

y = 5 * -7.6 + 5.5 = -32.5
Dynamical variable:
A = 2
B = 5
x = 6.6

y = 5 * 6.6 + 5.5 = 38.5
Three elemental static array:
Enter number A: 7.3
Enter number B: 3.3
Enter number A: 0.0
Enter number B: 5.5
Enter number A: 3.2
Enter number B: -7
A = 7.3
B = 3.3
A = 0
B = 5.5
A = 3.2
B = -7
Enter x quotients for three equations:
x1 = 9.5
x2 = -8.0
x3 = 7.7

y = 7.3 * 9.5 + 3.3 = 72.65

y = 0 * -8 + 5.5 = 5.5

y = 3.2 * 7.7 + -7 = 17.64
N elemental dynamical array:
N = 2

Enter number A: 6.6
Enter number B: 4.4
Enter number A: -3.0
Enter number B: 0
A = 6.6
B = 4.4
A = -3
B = 0
Enter x quotients for N equations::
x1 = 0
x2 = 3.3

y = 6.6 * 0 + 4.4 = 4.4

y = -3 * 3.3 + 0 = -9.9
Using function make_equation(a, b):
A = 3.3
B = 5.5
Output:
A = 3.3
B = 5.5


2)
Regular variable:
A = 3
B = 2.2
y = A * 4 + B = 14.2
Enter number A: rtrttttrr
According to you rtrttttrr - is a number?
C:\Users\Федор\Desktop\Б\Информатика\Лабы\1_class\Lab1\x64\Debug\Lab1.exe (процесс 13108) завершил работу с кодом 1.
Нажмите любую клавишу, чтобы закрыть это окно:


3)
Regular variable:
A = 3
B = 2.2
y = A * 4 + B = 14.2
Enter number A: 9999
Enter number B: 99999
A = 9999
B = 99999
x = 9

y = 9999 * 9 + 99999 = 189990
Dynamical variable:
A = 2
B = 5
x = 5

y = 9999 * 5 + 99999 = 149994
Three elemental static array:
Enter number A: 0
Enter number B: 0
Enter number A: 0
Enter number B: 0
Enter number A: 0
Enter number B: 0
A = 0
B = 0
A = 0
B = 0
A = 0
B = 0
Enter x quotients for three equations:
x1 = 0
x2 = 0
x3 = 0

y = 0 * 0 + 0 = 0

y = 0 * 0 + 0 = 0

y = 0 * 0 + 0 = 0
N elemental dynamical array:
N = 1

Enter number A: 23
Enter number B: 3.3
A = 23
B = 3.3
Enter x quotients for N equations::
x1 = 3

y = 23 * 3 + 3.3 = 72.3
Using function make_equation(a, b):
A = 3.3
B = 5.5
Output:
A = 3.3
B = 5.5
*/
```

## Тесты скриншоты

![Скриншот номер 1](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab1/screen/1.png)
![Скриншот номер 2](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab1/screen/2.png)
![Скриншот номер 3](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab1/screen/3.png)

## Ответы на вопросы

1. **Что такое класс?**

`Класс - это шаблон или чертеж, определяющий свойства (атрибуты) и поведение (методы) определенного типа объектов`.

2. **Что такое объект (экземпляр) класса?**

`Объект (экземпляр) класса - это конкретный экземпляр класса, который имеет состояние и поведение, определенное классом`.

3. **Как называются поля класса?**

`Поля класса (или атрибуты) - это переменные, которые хранят состояние объекта`.

4. **Как называются функции класса?**

`Функции класса (или методы) - это функции, которые определяют поведение объекта`.

5. **Для чего используются спецификаторы доступа?**

`Спецификаторы доступа используются для определения области видимости полей и методов класса`.

6. **Для чего используется спицификатор public?**

`Public - это спецификатор доступа, который позволяет доступ к полям и методам класса из любого места в коде`.

7. **Для чего используется спецификатор private?**

`Private - это спецификатор доступа, который ограничивает доступ к полям и методам класса только внутри самого класса`.

8. **Если описание  класса начинается со спецификатора class, то какой спецификатор доступа будет по умолчанию?**

`Если описание класса начинается со спецификатора class, то спецификатор доступа по умолчанию будет private`.

9. **Если описание  класса начинается со спецификатора struct, то какой спецификатор доступа будет по умолчанию?**

`Если описание класса начинается со спецификатора struct, то спецификатор доступа по умолчанию будет public`.

10. **Какой спецификатор доступа должен испольщоваться при описании интерфейса класса? Почему?**

`При описании интерфейса класса обычно используется спецификатор доступа public, потому что интерфейс предназначен для взаимодействия с другими частями кода`.

11. **Каким образом можно изменить значения атрибутов экземпляра класса?**

`Значения атрибутов экземпляра класса можно изменить, обратившись к ним напрямую (если они public) или через методы класса (getters и setters)`.

12. **Каким образом можно получить значения атрибутов экземпляра класса?**

`Значения атрибутов экземпляра класса можно получить, обратившись к ним напрямую (если они public) или через методы класса (getters)`.

13. **Класс описан следующим образом:**
```cpp
struct Student
{
	string name;
	int group;
};
```
**Объект класса определен следующим образом:**
```cpp
Student *s = new Student;
```
**Как можно обратиться к полю `name` объекта `s`?**

`s->name`.

14. **Класс описан следующим образом:**
```cpp
struct Student
{
	string name;
	int group;
};
```
**Объект класса определен следующим образом:**
```cpp
Student s;
```
**Как можно обратиться к полю `name` объекта `s`?**

`s.name`.

15. **Класс описан следующим образом:**
```cpp
class Student
{
	string name;
	int group;
};
```
**Объект класса определен следующим образом:**
```cpp
Student *s = new Student;
```
**Как можно обратиться к полю `name` объекта `s`?**

`Ответ: Так как поле name явлется private, нужно написать геттер, после чего можно получить доступ вот так: s->getName(), ниже пример реализации:`
```cpp
class Student
{
    string name;
    int group;
public:
    string getName()
    {
        return name;
    }
};

Student *s = new Student;
string studentName = s->getName();
```

16. **Класс описан следующим образом:**
```cpp
class Student
{
	string name;
	int group;
};
```
**Объект класса определен следующим образом:**
```cpp
Student s;
```
**Как можно обратиться к полю `name` объекта `s`?**

`Ответ: Так как поле name явлется private, нужно написать геттер, после чего можно получить доступ вот так: s.getName(), ниже пример реализации:`
```cpp
class Student
{
    string name;
    int group;
public:
    string getName()
    {
        return name;
    }
};

Student s;
string studentName = s.getName();
```

17. **Класс описан следующим образом:**
```cpp
class Student
{
public:
	char* name;
	int group;
};
```
**Объект класса определен следующим образом:**
```cpp
Student *s = new Student;
```
**Как можно обратиться к полю `name` объекта `s`?**

`Ответ: Так как мы точно не знаем, на что указывает char* name, предположим, что он указывает на реально существующую строку (массив символов, ведь имя не состоит из одного символа), тогда получить строку можно так:`
```cpp
class Student
{
public:
	char* name;
    int group;
};

Student *s = new Student;
char* nameAddress = s->name;
string studentName = nameAddress; // предполагая, что name - указатель массива символов, поэтому данная операция просто присвоит строке массив символов (но желательно знать размер)
```
