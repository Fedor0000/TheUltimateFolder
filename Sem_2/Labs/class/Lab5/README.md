# Лабораторная работа №5 "Наследование. Виртуальные функции. Полиморфизм."

## Постановка задачи

1. Определить абстрактный класс.
2. Определить иерархию классов, в основе которой будет находиться абстрактный
класс (см. лабораторную работу №4).
3. Определить класс Вектор, элементами которого будут указатели на объекты
иерархии классов.
4. Перегрузить для класса Вектор операцию вывода объектов с помощью потоков.
5. В основной функции продемонстрировать перегруженные операции и
полиморфизм Вектора.

### 7 Вариант:

Базовый класс:
ПАРА_ЧИСЕЛ (PAIR)
Первое_число (first) - int
Второе_число (second) – int
 - Определить методы проверки на равенство и операцию перемножения полей.
 - Реализовать операцию вычитания пар по формуле (a,b)-(c,d)=(a-b,c-d)
 - Создать производный класс ПРОСТАЯ_ДРОБЬ(RATIONAL), с полями Числитель и Знаменатель. Переопределить операцию вычитания и определить операции сложения и умножения простых дробей.

## UML-диаграмма

![uml](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab5/uml.png)

## Код программы

`object.h`
```cpp
#pragma once
class Object
{
public:
	Object();
	~Object();
	virtual void Show() = 0;
};
```

`object.cpp`
```cpp
#pragma once
#include "object.h"
Object::Object() {}
Object::~Object() {}
```

`pair.h`
```cpp
#pragma once
#include "object.h"
#include <string>
#include <iostream>
using namespace std;
class Pair : public Object
{
public:
	Pair();
	virtual ~Pair();
	void Show();
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
void Pair::Show()
{
	cout << "Первое число: " << first << endl;
	cout << "Второе число: " << second << endl;
}
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
	void Show();
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
void SimpleFraction::Show()
{
	cout << "Числитель: " << first << endl;
	cout << "Знаменатель: " << second << endl;
}
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

`vector.h`
```cpp
#pragma once
#include "object.h"
#include <string>
#include <iostream>
using namespace std;
class Vector
{
public:
	Vector();
	Vector(int);
	~Vector();
	void Add(Object*);
	friend ostream& operator<<(ostream& out, const Vector&);
private:
	Object** beg;
	int size;
	int cur;
};
```

`vector.cpp`
```cpp
#pragma once
#include "Vector.h"
Vector::Vector()
{
	beg = 0;
	size = 0;
	cur = 0;
}
Vector::~Vector()
{
	if (beg != 0) delete[] beg;
	beg = 0;
}
Vector::Vector(int n)
{
	beg = new Object * [n];
	cur = 0;
	size = n;
}
void Vector::Add(Object* p)
{
	if (cur < size)
	{
		beg[cur] = p;
		cur++;
	}
}
ostream& operator<<(ostream& out, const Vector& v)
{
	if (v.size == 0) out << "Вектор пуст." << endl;
	Object** p = v.beg;
	for (int i = 0; i < v.cur; i++)
	{
		(*p)->Show();
		p++;
	}
	return out;
}
```

`main.cpp`
```cpp
#include "Object.h"
#include "pair.h"
#include "simpleFraction.h"
#include "Vector.h"
#include <string>
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	Vector v(5);
	Pair a;
	cin >> a;
	SimpleFraction b;
	cin >> b;
	Object* p = &a;
	v.Add(p);
	p = &b;
	v.Add(p);
	cout << v;
	return 0;
}
```

## Тесты текстом

```cpp
/*
1)
Введите первое число пары: -35
Введите второе число пары: 89
Введите числитель 65
Введите знаменатель 5
Первое число: -35
Второе число: 89
Числитель: 65
Знаменатель: 5

2)
Введите первое число пары: 3469734
Введите второе число пары: -2362
Введите числитель 82538
Введите знаменатель 92323
Первое число: 3469734
Второе число: -2362
Числитель: 82538
Знаменатель: 92323

3)
Введите первое число пары: 76726
Введите второе число пары: 982
Введите числитель -8787
Введите знаменатель 232
Первое число: 76726
Второе число: 982
Числитель: -8787
Знаменатель: 232
*/
```

## Тесты скриншоты

![Скриншот номер 1](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab5/screen/1.png)
![Скриншот номер 2](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab5/screen/2.png)
![Скриншот номер 3](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab5/screen/3.png)

## Ответы на вопросы

**1. Какой метод называется чисто виртуальным? Чем он отличается от виртуального метода?**

`1. Чисто виртуальный метод (или абстрактный метод) — это метод, который объявлен в базовом классе, но не имеет реализации в этом классе. Он служит только для определения интерфейса, и его реализация ожидается в производных классах. Виртуальные методы, с другой стороны, имеют реализацию в базовом классе, но могут быть переопределены в производных классах.`

**2. Какой класс называется абстрактным?**

`Абстрактный класс — это класс, который содержит хотя бы один чисто виртуальный метод. Это означает, что он не может быть инстанциирован напрямую, а его цель — служить базой для других классов.`

**3. Для чего предназначены абстрактные классы?**

`Абстрактные классы предназначены для следующих целей:`

`1. Определения общего интерфейса для группы связанных классов.`

`2. Предоставления базовой реализации для методов, которые должны быть переопределены в производных классах.`

`3. Запрета инстанцирования самого абстрактного класса.`

**4. Что такое полиморфные функции?**

`Полиморфные функции — это функции, которые могут принимать аргументы разных типов и вести себя по-разному в зависимости от типа аргументов. Это позволяет обращаться к одной и той же функции с разными типами данных.`

**5. Чем полиморфизм отличается от принципа подстановки?**

`Полиморфизм — это более широкий принцип, который означает способность объектов разных классов обрабатывать одинаковые операции. Принцип подстановки — это часть полиморфизма и утверждает, что объекты производных классов могут безопасно использоваться вместо объектов базовых классов.`

**6. Привести примеры иерархий с использованием абстрактных классов.**

`Геометрические фигуры: базовый абстрактный класс “Фигура” с методами для вычисления площади и периметра, от которого наследуются конкретные фигуры (круг, прямоугольник, треугольник).`

`Транспортные средства: базовый абстрактный класс “Транспорт” с методами для движения и остановки, от которого наследуются автомобили, велосипеды и другие виды транспорта.`

**7. Привести примеры полиморфных функций.**

`Функция “вывести информацию” может принимать разные типы объектов (например, фигуры или транспортные средства) и выводить их характеристики.`

`Метод “подсчитать площадь” может работать с разными типами геометрических фигур (кругами, прямоугольниками и т. д.) и возвращать соответствующие значения.`

**8. В каких случаях используется механизм позднего связывания?**

`Механизм позднего связывания используется, когда вызов метода происходит во время выполнения программы, а не на этапе компиляции. Это позволяет выбирать правильную реализацию метода в зависимости от типа объекта, на котором он вызывается. Позднее связывание обеспечивает гибкость и расширяемость кода.`
