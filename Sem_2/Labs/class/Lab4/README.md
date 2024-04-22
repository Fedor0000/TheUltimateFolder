# Лабораторная работа №4 "Простое наследование. Принцип подстановки."

## Постановка задачи

1. Определить пользовательский класс.
2. Определить в классе следующие конструкторы: без параметров, с параметрами,
копирования.
3. Определить в классе деструктор.4. Определить в классе компоненты-функции для просмотра и установки полей
данных (селекторы и модификаторы).
5. Перегрузить операцию присваивания.
6. Перегрузить операции ввода и вывода объектов с помощью потоков.
7. Определить производный класс.
8. Написать программу, в которой продемонстрировать создание объектов и работу
всех перегруженных операций.
9. Реализовать функции, получающие и возвращающие объект базового класса.
Продемонстрировать принцип подстановки.

### 7 Вариант:

Базовый класс:
ПАРА_ЧИСЕЛ (PAIR)
Первое_число (first) - int
Второе_число (second) – int
 - Определить методы проверки на равенство и операцию перемножения полей.
 - Реализовать операцию вычитания пар по формуле (a,b)-(c,d)=(a-b,c-d)
 - Создать производный класс ПРОСТАЯ_ДРОБЬ(RATIONAL), с полями Числитель и Знаменатель. Переопределить операцию вычитания и определить операции сложения и умножения простых дробей.

## UML-диаграмма

![uml](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab4/uml.png)

## Код программы

`pair.h`
```cpp
#pragma once
#include <string>
#include <iostream>
using namespace std;
class Pair
{
public:
	Pair();
	virtual ~Pair();
	Pair(int, int);
	Pair(const Pair&);
	int getFirst()
	{
		return first;
	}
	int getSecond()
	{
		return second;
	}
	bool isEqual()
	{
		return (first == second ? true : false);
	}
	int product()
	{
		return first * second;
	}
	void setFirst(int);
	void setSecond(int);
	Pair& operator=(const Pair&);
	bool operator==(const Pair&);
	Pair operator-(const Pair&);
	friend istream& operator>>(istream& in, Pair& c);
	friend ostream& operator<<(ostream& out, const Pair& c);
protected:
	int first;
	int second;
};
```

`pair.cpp`
```cpp
#pragma once
#include "pair.h"
Pair::Pair()
{
	first = 0;
	second = 0;
}
Pair::~Pair() {}
Pair::Pair(int f, int s)
{
	first = f;
	second = s;
}
Pair::Pair(const Pair& pair)
{
	first = pair.first;
	second = pair.second;
}
void Pair::setFirst(int f)
{
	first = f;
}
void Pair::setSecond(int s)
{
	second = s;
}
Pair& Pair::operator=(const Pair& p)
{
	if (&p == this) return *this;
	first = p.first;
	second = p.second;
	return *this;
}
bool Pair::operator==(const Pair& p)
{
	if ((first == p.first) && (second == p.second)) return true;
	else return false;
}
Pair Pair::operator-(const Pair& p)
{
	Pair sub;
	sub.first = first - second;
	sub.second = p.first - p.second;
	return sub;
}
istream& operator>>(istream& in, Pair& c)
{
	cout << "Введите первое число пары: ";
	in >> c.first;
	cout << "Введите второе число пары: ";
	in >> c.second;
	return in;
}
ostream& operator<<(ostream& out, const Pair& p)
{
	out << "Первое число пары: " << p.first << endl;
	out << "Второе число пары: " << p.second << endl;
	return out;
}
```

`simpleFraction.h`
```cpp
#pragma once
#include "pair.h"
class SimpleFraction : public Pair
{
public:
	SimpleFraction();
	~SimpleFraction();
	SimpleFraction(int, int);
	SimpleFraction(const SimpleFraction&);
	SimpleFraction operator-(const SimpleFraction&);
	SimpleFraction operator+(const SimpleFraction&);
	SimpleFraction operator*(const SimpleFraction&);
	friend istream& operator>>(istream& in, SimpleFraction& l);
	friend ostream& operator<<(ostream& out, const SimpleFraction& l);
};
```

`simpleFraction.cpp`
```cpp
#pragma once
#include "simpleFraction.h"
int noz(int a, int b)
{
	int nozz = max(a, b);
	while (!(!((nozz % a != 0)) && !((nozz % b != 0)))) nozz++;
	return nozz;
}
SimpleFraction::SimpleFraction() : Pair() {}
SimpleFraction::~SimpleFraction() {}
SimpleFraction::SimpleFraction(int f, int s) : Pair(f, s) {}
SimpleFraction::SimpleFraction(const SimpleFraction& L)
{
	first = L.first;
	second = L.second;
}
SimpleFraction SimpleFraction::operator-(const SimpleFraction& f)
{
	int znam = noz(second, f.second);
	int dop1 = znam / second;
	int dop2 = znam / f.second;
	SimpleFraction result;
	result.second = znam;
	result.first = first * dop1 - f.first * dop2;
	return result;
}
SimpleFraction SimpleFraction::operator+(const SimpleFraction& f)
{
	int znam = noz(second, f.second);
	int dop1 = znam / second;
	int dop2 = znam / f.second;
	SimpleFraction result;
	result.second = znam;
	result.first = first * dop1 + f.first * dop2;
	return result;
}
SimpleFraction SimpleFraction::operator*(const SimpleFraction& p)
{
	SimpleFraction product;
	product.first = first * p.first;
	product.second = second * p.second;
	return product;
}
istream& operator>>(istream& in, SimpleFraction& l)
{
	cout << "Введите числитель ";
	in >> l.first;
	cout << "Введите знаменатель ";
	in >> l.second;
	return in;
}
ostream& operator<<(ostream& out, const SimpleFraction& l)
{
	string str1 = to_string(l.first);
	string str2 = to_string(l.second);
	int size = max(str1.size(), str2.size());
	int strsize = str1.size();
	for (int i = 0; i < (((size + 2) / 2 - strsize) + 1); i++) out << " ";
	out << l.first << endl;
	for (int i = 0; i < size+2; i++)
	{
		out << "-";
	}
	out << endl;
	out << " " << l.second << endl;
	return out;
}
```

`main.cpp`
```cpp
#include <iostream>
#include "pair.h"
#include "simpleFraction.h"
using namespace std;
void f1(Pair& c)
{
	int f;
	cout << "Введите новое первое число пары: ";
	cin >> f;
	c.setFirst(f);
	cout << c;
}
Pair f2()
{
	int i, j;
	cout << "Введите два числа через пробел для создания дроби: ";
	cin >> i >> j;
	SimpleFraction l(i, j);
	return l;
}
void main()
{
	setlocale(LC_ALL, "Russian");
	Pair a;
	cin >> a;
	cout << a;
	cout << "Первое число пары А: " << a.getFirst() << endl << "Второе число пары А: " << a.getSecond() << endl;
	if (a.isEqual()) cout << "Пара A состоит из одинаковых чисел." << endl;
	else cout << "Числа в паре A разные." << endl;
	cout << "Вот что будет, если перемножить числа в паре A: " << a.product() << endl;
	cout << "Пара B. Конструктор с параметрами Ъ и Ь:" << endl;
	int tv, mg;
	cout << "Введите параметры:" << endl << "Ъ = ";
	cin >> tv;
	cout << "Ь = ";
	cin >> mg;
	Pair b(tv, mg);
	cout << b;
	if (a == b) cout << "Пары полностью идентичны." << endl;
	else cout << "Пары НЕ полностью идентичны." << endl;
	cout << "Вычитание пар по формуле: (А_первое, А_второе) - (В_первое, В_второе) = (А_первое - А_второе, В_первое, В_второе):" << endl << a - b;
	a = b;
	cout << "Теперь А = В, вывод нового А: " << endl;
	cout << a;
	SimpleFraction c, d;
	cin >> c;
	cin >> d;
	cout << c << endl;
	cout << d;
	cout << "Вычтем из дроби С дробь Д:" << endl << c - d;
	cout << "Сложим дроби С и Д:" << endl << c + d;
	cout << "Перемножим дроби С и Д:" << endl << c * d;
	cout << "Изменим первое число дроби С и превратим ее в пару:" << endl;
	f1(c);
	cout << "Создадим дробь, но выведем как пару: " << endl;
	a = f2();
	cout << a;
}
```

## Тесты текстом

```cpp
/*
1)
Введите первое число пары: 6
Введите второе число пары: 6
Первое число пары: 6
Второе число пары: 6
Первое число пары А: 6
Второе число пары А: 6
Пара A состоит из одинаковых чисел.
Вот что будет, если перемножить числа в паре A: 36
Пара B. Конструктор с параметрами Ъ и Ь:
Введите параметры:
Ъ = 89
Ь = -1
Первое число пары: 89
Второе число пары: -1
Пары НЕ полностью идентичны.
Вычитание пар по формуле: (А_первое, А_второе) - (В_первое, В_второе) = (А_первое - А_второе, В_первое, В_второе):
Первое число пары: 0
Второе число пары: 90
Теперь А = В, вывод нового А:
Первое число пары: 89
Второе число пары: -1
Введите числитель 1
Введите знаменатель 10
Введите числитель 1
Введите знаменатель 15
  1
----
 10

  1
----
 15
Вычтем из дроби С дробь Д:
  1
----
 30
Сложим дроби С и Д:
  5
----
 30
Перемножим дроби С и Д:
  1
-----
 150
Изменим первое число дроби С и превратим ее в пару:
Введите новое первое число пары: 23
Первое число пары: 23
Второе число пары: 10
Создадим дробь, но выведем как пару:
Введите два числа через пробел для создания дроби: 34 56
Первое число пары: 34
Второе число пары: 56

2)
Введите первое число пары: -4
Введите второе число пары: 67
Первое число пары: -4
Второе число пары: 67
Первое число пары А: -4
Второе число пары А: 67
Числа в паре A разные.
Вот что будет, если перемножить числа в паре A: -268
Пара B. Конструктор с параметрами Ъ и Ь:
Введите параметры:
Ъ = -4
Ь = 67
Первое число пары: -4
Второе число пары: 67
Пары полностью идентичны.
Вычитание пар по формуле: (А_первое, А_второе) - (В_первое, В_второе) = (А_первое - А_второе, В_первое, В_второе):
Первое число пары: -71
Второе число пары: -71
Теперь А = В, вывод нового А:
Первое число пары: -4
Второе число пары: 67
Введите числитель 1
Введите знаменатель 10
Введите числитель -1
Введите знаменатель 15
  1
----
 10

 -1
----
 15
Вычтем из дроби С дробь Д:
  5
----
 30
Сложим дроби С и Д:
  1
----
 30
Перемножим дроби С и Д:
 -1
-----
 150
Изменим первое число дроби С и превратим ее в пару:
Введите новое первое число пары: 10
Первое число пары: 10
Второе число пары: 10
Создадим дробь, но выведем как пару:
Введите два числа через пробел для создания дроби: -12 52
Первое число пары: -12
Второе число пары: 52

3)
Введите первое число пары: 87
Введите второе число пары: 34
Первое число пары: 87
Второе число пары: 34
Первое число пары А: 87
Второе число пары А: 34
Числа в паре A разные.
Вот что будет, если перемножить числа в паре A: 2958
Пара B. Конструктор с параметрами Ъ и Ь:
Введите параметры:
Ъ = 9
Ь = 999
Первое число пары: 9
Второе число пары: 999
Пары НЕ полностью идентичны.
Вычитание пар по формуле: (А_первое, А_второе) - (В_первое, В_второе) = (А_первое - А_второе, В_первое, В_второе):
Первое число пары: 53
Второе число пары: -990
Теперь А = В, вывод нового А:
Первое число пары: 9
Второе число пары: 999
Введите числитель 56
Введите знаменатель 127
Введите числитель 4
Введите знаменатель 13
 56
-----
 127

  4
----
 13
Вычтем из дроби С дробь Д:
 220
------
 1651
Сложим дроби С и Д:
1236
------
 1651
Перемножим дроби С и Д:
 224
------
 1651
Изменим первое число дроби С и превратим ее в пару:
Введите новое первое число пары: 233
Первое число пары: 233
Второе число пары: 127
Создадим дробь, но выведем как пару:
Введите два числа через пробел для создания дроби: 2222 1111
Первое число пары: 2222
Второе число пары: 1111
*/
```

## Тесты скриншоты

![Скриншот номер 1](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab4/screen/1.png)
![Скриншот номер 2](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab4/screen/2.png)
![Скриншот номер 3](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab4/screen/3.png)

## Ответы на вопросы

**1. Для чего используется механизм наследования?**

`Механизм наследования используется для создания новых классов на основе существующих. Он позволяет классам наследовать свойства и методы других классов, что способствует повторному использованию кода.`

**2. Каким образом наследуются компоненты класса, описанные со спецификатором public?**

`Компоненты класса, описанные со спецификатором public, наследуются также с модификатором public в производном классе. Это означает, что они остаются доступными извне.`

**3. Каким образом наследуются компоненты класса, описанные со спецификатором private?**

`Компоненты класса, описанные со спецификатором private, не наследуются в производном классе. Они остаются закрытыми и недоступными извне.`

**4. Каким образом наследуются компоненты класса, описанные со спецификатором protected?**

`Компоненты класса, описанные со спецификатором protected, наследуются с модификатором protected в производном классе. Они доступны внутри производного класса и его потомков.`

**5. Каким образом описывается производный класс?**

`Производный класс описывается путем создания нового класса, который наследует свойства и методы от базового класса. Синтаксис: class Derived : public Base { ... }.`

**6. Наследуются ли конструкторы?**

`Конструкторы наследуются, но они не вызываются автоматически. В производном классе можно явно вызвать конструктор базового класса.`

**7. Наследуются ли деструкторы?**

`Деструкторы также наследуются, но также не вызываются автоматически. Важно убедиться, что деструктор базового класса объявлен как виртуальный.`

**8. В каком порядке конструируются объекты производных классов?**

`Объекты производных классов конструируются в следующем порядке:`

`1. Вызывается конструктор базового класса.`

`2. Выполняются инициализации производного класса.`

`3. Вызывается конструктор производного класса.`

**9. В каком порядке уничтожаются объекты производных классов?**

`1. Вызывается деструктор производного класса.`

`2. Выполняются действия деструктора базового класса.`

**10. Что представляют собой виртуальные функции и механизм позднего связывания?**

`Виртуальные функции позволяют проводить динамическое связывание. Они определяются в базовом классе и могут быть переопределены в производных классах. Механизм позднего связывания обеспечивает вызов правильной функции во время выполнения.`

**11. Могут ли быть виртуальными конструкторы? Деструкторы?**

`Конструкторы не могут быть виртуальными, но деструкторы могут. Виртуальные деструкторы обеспечивают корректное удаление объектов при использовании указателей на базовый класс.`

**12. Наследуется ли спецификатор virtual?**

`Спецификатор virtual не наследуется, но его использование в производном классе позволяет переопределить функцию как виртуальную.`

**13. Какое отношение устанавливает между классами открытое наследование?**

`Открытое наследование устанавливает отношение “является” между базовым и производным классами.`

**14. Какое отношение устанавливает между классами закрытое наследование?**

`Закрытое наследование устанавливает отношение “реализует” между базовым и производным классами.`

**15. В чем заключается принцип подстановки?**

`Принцип подстановки заключается в том, что объект производного класса может использоваться везде, где используется объект базового класса.`

**16. Имеется иерархия классов:**
```cpp
class Student
{
	int age;
public:
	string name;
	...
};
class Employee : public Student
{
protected:
	string post;
	...
};
class Teacher : public Employee
{
	protected: int stage;
	...
};

Teacher x;
```
**Какие компонентные данные будет иметь объект х?**

`Объект x принадлежит классу Teacher, который наследует свойства от класса Employee, а тот, в свою очередь, наследует свойства от класса Student.`

`Поэтому объект x будет иметь следующие компонентные данные:`

`public     name (наследовано от класса Student).`

`protected  post (наследовано от класса Employee).`

`protected  stage (собственное свойство класса Teacher).`

**17. Для классов Student, Employee и Teacher написать конструкторы без параметров.**

```cpp
class Student
{
public:
    Student()
	{
		age = 0;
		name = " ";
	}
};
class Employee : public Student
{
public:
    Employee() : Student()
	{
		post = " ";
	}
};
class Teacher : public Employee
{
public:
    Teacher() : Employee()
	{
		stage = 0;
	}
};
```

**18. Для классов Student, Employee и Teacher написать конструкторы с параметрами.**

```cpp
class Student
{
public:
    Student(int a, string n)
	{
		age = a;
		name = n;
	}
};
class Employee : public Student
{
public:
    Employee(string n, string p) : Student(a, n)
	{
		post = p;
	}
};
class Teacher : public Employee
{
public:
    Teacher(string n, string p, int s) : Employee(n, p)
	{
		stage = s;
	}
};
```

**19. Для классов Student, Employee и Teacher написать конструкторы копирования.**

```cpp
class Student
{
public:
    Student(const Student& S)
	{
		age = S.age;
		name = S.name;
	}
};
class Employee : public Student
{
public:
    Employee(const Employee& E)
	{
		name = E.name;
		post = E.post;
	}
};
class Teacher : public Employee
{
public:
    Teacher(const Teacher& T)
	{
		name = T.name;
		post = T.post;
		stage = T.stage;
	}
};
```

**20. Для классов Student, Employee и Teacher определить операцию присваивания.**

```cpp
Student operator=(const Student& S)
{
	if (&S==this) return *this;
	age = S.age;
	name = S.name;
	return *this;
}
Employee operator=(const Employee& E)
{
	if (&S==this) return *this;
	name = E.name;
	post = E.post;
	return *this;
}
Teacher operator=(const Teacher& T)
{
	if (&S==this) return *this;
	name = T.name;
	post = T.post;
	stage = T.stage;
	return *this;
}
```
