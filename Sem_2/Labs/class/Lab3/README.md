# Лабораторная работа №3 "Перегрузка операций"

## Постановка задачи

1. Определить пользовательский класс.
2. Определить в классе следующие конструкторы: без параметров, с параметрами,
копирования.
3. Определить в классе деструктор.
4. Определить в классе компоненты-функции для просмотра и установки полей
данных (селекторы и модификаторы).
5. Перегрузить операцию присваивания.
6. Перегрузить операции ввода и вывода объектов с помощью потоков.
7. Перегрузить операции указанные в варианте.
8. Написать программу, в которой продемонстрировать создание объектов и работу
всех перегруженных операций.

### 7 Вариант:

Создать класс Money для работы с денежными суммами. Число должно быть представлено двумя полями: типа long для рублей и типа int для копеек. Дробная часть числа при выводе на экран должна быть отделена от целой части запятой. Реализовать:
 - деление сумм;
 - умножение суммы на дробное число.

## UML-диаграмма

![uml](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab3/uml.png)

## Код программы

`money.h`
```cpp
#pragma once
#include <iostream>
using namespace std;
class Money
{
	long long int rubles;
	int kopecks;
public:
	Money()
	{
		rubles = 0;
		kopecks = 0;
	}
	Money(long long int r, int k)
	{
		rubles = r;
		kopecks = k;
	}
	Money(const Money& t)
	{
		rubles = t.rubles;
		kopecks = t.kopecks;
	}
	~Money() {};
	int getRubles()
	{
		return rubles;
	}
	int getKopecks()
	{
		return kopecks;
	}
	void setRubles(long long int r)
	{
		rubles = r;
	}
	void setKopecks(int k)
	{
		kopecks = k;
	}
	Money& operator=(const Money&);
	Money& operator++(); // префиксная
	Money& operator--(); // префиксная
	Money operator++(int); //постфиксная
	Money operator--(int); //постфиксная
	Money operator+(const Money&);
	Money operator-(const Money&);
	Money operator*(const Money&);
	Money operator/(const Money&);
	Money operator*(const double&);
	Money operator/(const double&);
	friend istream& operator>>(istream& in, Money& t);
	friend ostream& operator<<(ostream& out, const Money& t);
};
```

`money.cpp`
```cpp
#pragma once
#include "money.h"
#include <iostream>
using namespace std;
Money& Money::operator=(const Money& t)
{
	if (&t == this) return *this;
	rubles = t.rubles;
	kopecks = t.kopecks;
	return *this;
}
Money& Money::operator++() // префиксная операция
{
	rubles++;
	return *this;
}
Money& Money::operator--() // префиксная операция
{
	rubles--;
	return *this;
}
Money Money::operator ++(int) // постфиксная операция
{
	int temp = rubles;
	temp++;
	Money t(temp, kopecks);
	return t;
}
Money Money::operator--(int) // постфиксная операция
{
	Money tmp = *this;
	tmp.rubles--;
	return tmp;
}
Money Money::operator+(const Money& t)
{
	long long int rub = rubles;
	long long int rub2 = t.rubles;
	int  kop = kopecks;
	int kop2 = t.kopecks;
	int buf;
	Money summa;
	summa.rubles = rub + rub2;
	summa.kopecks = (kop + kop2) % 100;
	buf = (kop + kop2) / 100;
	summa.rubles += buf;
	return summa;
}
Money Money::operator-(const Money& t)
{
	long long int rub = rubles;
	long long int rub2 = t.rubles;
	int kop = kopecks;
	int kop2 = t.kopecks;
	long long int allKopecks1 = rub * 100 + kop;
	long long int allKopecks2 = rub2 * 100 + kop2;
	Money sub;
	sub.kopecks = (allKopecks1 - allKopecks2) % 100;
	sub.rubles = (allKopecks1 - allKopecks2) / 100;
	return sub;
}
Money Money::operator*(const Money& t)
{
	long long int rub = rubles;
	long long int rub2 = t.rubles;
	int  kop = kopecks;
	int kop2 = t.kopecks;
	int buf;
	long long int allKopecks1 = rub * 100 + kop;
	long long int allKopecks2 = rub2 * 100 + kop2;
	buf = allKopecks1 * allKopecks2;
	Money product;
	product.rubles = 0;
	product.kopecks = buf % 10000 / 100;
	product.rubles += buf/10000;
	return product;
}
Money Money::operator/(const Money& t)
{
	long long int rub = rubles;
	long long int rub2 = t.rubles;
	int  kop = kopecks;
	int kop2 = t.kopecks;
	double buf;
	long double allKopecks1 = rub * 100 + kop;
	long double allKopecks2 = rub2 * 100 + kop2;
	buf = allKopecks1 / allKopecks2;
	Money divided;
	divided.rubles = buf;
	buf -= abs(divided.rubles);
	buf *= 100;
	divided.kopecks = buf;
	return divided;
}
Money Money::operator*(const double& t)
{
	long long int rub = rubles;
	int kop = kopecks;
	int buf;
	long long int allKopecks = rub * 100 + kop;
	buf = allKopecks * t;
	Money divided;
	divided.rubles = 0;
	divided.kopecks = buf % 100;
	divided.rubles += buf / 100;
	return divided;
}
Money Money::operator/(const double& t)
{
	long long int rub = rubles;
	int kop = kopecks;
	int buf;
	long long int allKopecks = rub * 100 + kop;
	buf = allKopecks / t;
	Money divided;
	divided.rubles = 0;
	divided.kopecks = buf % 100;
	divided.rubles += buf / 100;
	return divided;
}
istream& operator>>(istream& in, Money& t)
{
	cout << "Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): ";
	in >> t.rubles;
	cout << "Введите копейки без рублей: "; in >> t.kopecks;
	if (abs(t.kopecks) >= 100)
	{
		int buf = t.kopecks / 100;
		t.rubles += buf;
		t.kopecks = t.kopecks % 100;
	}
	return in;
}
ostream& operator<<(ostream& out, const Money& t)
{
	int boof = t.kopecks;
	if (t.kopecks < 0)
	{
		boof = -t.kopecks;
	}
	if ((t.rubles == 0) && (t.kopecks < 0))
	{
		if (boof >= 10)
		{
			return (out << "-" << t.rubles << "," << boof);
		}
		else
		{
			return (out << "-" << t.rubles << "," << 0 << boof);
		}
	}
	else if (boof >= 10)
	{
		return (out << t.rubles << "," << boof);
	}
	else
	{
		return (out << t.rubles << "," << 0 << boof);
	}
}
```

`main.cpp`
```cpp
#include <iostream>
#include "money.h"
using namespace std;
int main()
{
	system("chcp 1251 > null");
	Money a;
	Money b;
	Money c;
	double number;
	cin >> a;
	cin >> b;
	cout << "Введите число, для выполнения действий с денежными суммами: ";
	cin >> number;
	cout << "Первая сумма " << a << endl;
	cout << "Вторая сумма " << b << endl;
	++a;
	cout << "Первая сумма, увеличенная на 1: " << a << endl;
	--a;
	c = a / number;
	cout << "Первая сумма деленная на введеное число " << c << endl;
	c = a * number;
	cout << "Первая сумма умнноженная на введеное число: " << c << endl;
	c = a / b;
	cout << "Первая сумма деленная на вторую " << c << endl;
	c = a * b;
	cout << "Первая сумма умноженная на вторую " << c << endl;
	c = a - b;
	cout << "Первая сумма минус вторая " << c << endl;
	c = a + b;
	cout << "Первая сумма плюс вторая " << c << endl;
	cout << "Рубли первой суммы: " << a.getRubles() << endl;
	cout << "Копейки первой суммы: " << a.getKopecks() << endl;
	Money d(a);
	cout << "Копия первой суммы " << d << endl;
	Money e(23, 24);
	cout << "Конструктор с параметрами 23 и 24 " << e << endl;
	e.setKopecks(1);
	e.setRubles(1);
	cout << "Изменение через сеттеры " << e << endl;
	return 0;
}
```

## Тесты текстом

```cpp
/*
1)
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 0
Введите копейки без рублей: -439
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 56
Введите копейки без рублей: 9
Введите число, для выполнения действий с денежными суммами: 3.45
Первая сумма -4,39
Вторая сумма 56,09
Первая сумма, увеличенная на 1: -3,39
Первая сумма деленная на введеное число -1,27
Первая сумма умнноженная на введеное число: -15,14
Первая сумма деленная на вторую -0,07
Первая сумма умноженная на вторую -246,23
Первая сумма минус вторая -60,48
Первая сумма плюс вторая 52,30
Рубли первой суммы: -4
Копейки первой суммы: -39
Копия первой суммы -4,39
Конструктор с параметрами 23 и 24 23,24
Изменение через сеттеры 1,01

2)
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 343
Введите копейки без рублей: 3333
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 0
Введите копейки без рублей: 1
Введите число, для выполнения действий с денежными суммами: 2.2
Первая сумма 376,33
Вторая сумма 0,01
Первая сумма, увеличенная на 1: 377,33
Первая сумма деленная на введеное число 171,05
Первая сумма умнноженная на введеное число: 827,92
Первая сумма деленная на вторую 37633,00
Первая сумма умноженная на вторую 3,76
Первая сумма минус вторая 376,32
Первая сумма плюс вторая 376,34
Рубли первой суммы: 376
Копейки первой суммы: 33
Копия первой суммы 376,33
Конструктор с параметрами 23 и 24 23,24
Изменение через сеттеры 1,01

3)
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): -3
Введите копейки без рублей: -98
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): -23
Введите копейки без рублей: -2
Введите число, для выполнения действий с денежными суммами: 34.5
Первая сумма -3,98
Вторая сумма -23,02
Первая сумма, увеличенная на 1: -2,98
Первая сумма деленная на введеное число -0,11
Первая сумма умнноженная на введеное число: -137,31
Первая сумма деленная на вторую 0,17
Первая сумма умноженная на вторую 91,61
Первая сумма минус вторая 19,04
Первая сумма плюс вторая -27,00
Рубли первой суммы: -3
Копейки первой суммы: -98
Копия первой суммы -3,98
Конструктор с параметрами 23 и 24 23,24
Изменение через сеттеры 1,01
*/
```

## Тесты скриншоты

![Скриншот номер 1](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab3/screen/1.png)
![Скриншот номер 2](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab3/screen/2.png)
![Скриншот номер 3](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab3/screen/3.png)

## Ответы на вопросы

**1. Для чего используются дружественные функции и классы?**

`Дружественные функции и классы в C++ используются для предоставления доступа к закрытым (private) членам другого класса.`

`Дружественные функции не являются членами класса, но имеют доступ к его приватным переменным и функциям.`

`Для определения дружественных функций используется ключевое слово friend.`

**2. Сформулировать правила описания и особенности дружественных функций.**

`Дружественные функции могут быть определены внутри класса или в другом классе`.

`Для них не важно, определены ли они под спецификатором public или private`.

`Они имеют доступ ко всем членам класса, включая закрытые.`

**3. Каким образом можно перегрузить унарные операции?**

`Унарные операции могут быть перегружены для пользовательских типов данных (классов).`

`Для перегрузки унарных операций используются специальные методы класса (например, operator+, operator-, operator++, operator--, они были применены в этой лабораторной работе).`

`При перегрузки оператора мы можем заставить его выполнять какие угодно действия над объектом нашего класса`

**4. Сколько операндов должна иметь унарная функция-операция, определяемая внутри класса?**

`Унарная функция-операция, определенная внутри класса, должна иметь от нуля до одного операнда (параметра) в явном виде, так как объект класса в данном случае передаётся неявно, как this.`

**5. Сколько операндов должна иметь унарная функция-операция, определяемая вне класса?**

`Унарная функция-операция, определенная вне класса, должна иметь один операнд в явном виде, так как она не получает this.`

**6. Сколько операндов должна иметь бинарная функция-операция, определяемая внутри класса?**

`Бинарная функция-операция, определенная внутри класса, должна иметь один-два операнда (параметра) в явном виде по причинам, описанным выше.`

**7. Сколько операндов должна иметь бинарная функция-операция, определяемая вне класса?**

`Бинарная функция-операция, определенная вне класса, должна иметь два операнда в явном виде, так как она не получает this.`

**8. Чем отличается перегрузка префиксных и постфиксных унарных операций?**

`Префиксная форма (например, ++x) возвращает измененное значение до выполнения операции.`
`Постфиксная форма (например, x++) возвращает исходное значение, а затем выполняет операцию.`
`При перегрузке постфиксного оператора важно писать в круглых скобках int, например, operator--(int).`

**9. Каким образом можно перегрузить операцию присваивания?**

`Операция присваивания (=) может быть перегружена для пользовательских типов данных. Для этого используется метод operator= внутри класса.`

**10. Что должна возвращать операция присваивания?**

`Операция присваивания (=) должна возвращать ссылку на объект, чтобы обеспечить возможность цепочки присваиваний (например, a = b = c = 42;).`

**11. Каким образом можно перегрузить операции ввода-вывода?**

`Перегрузка операций ввода-вывода в C++ позволяет пользовательским типам данных (классам) определить собственное поведение при вводе и выводе объектов. Для этого используются методы operator>> и operator<<. Для корректной работы перегрузку надо описывать вне класса, как дружественную функцию. Примером использования служит данная лабораторная работа.`

**12. В программе описан класс**
```cpp
class Student
{
	Student& operator++();
};
```
**и определен объект этого класса**
```cpp
Student s;
```
**Выполняется операция**
```cpp
++s;
```
**Каким образом, компилятор будет воспринимать вызов функции-операции?**

`В данном случае, компилятор будет воспринимать вызов функции-операции префиксного инкремента (++s) следующим образом:`

`Оператор ++ будет применяться к объекту s, вызывая метод operator++() внутри класса Student.`

`Метод operator++() должен изменить состояние объекта s и вернуть ссылку на него (тип Student&).`

**13. В программе описан класс**
```cpp
class Student
{
	friend Student& operator ++( Student&);
};
```
**и определен объект этого класса**
```cpp
Student s;
```
**Выполняется операция**
```cpp
++s;
```
**Каким образом, компилятор будет воспринимать вызов функции-операции?**

`Если оператор ++ перегружен как дружественная функция, то компилятор будет воспринимать вызов следующим образом:`

`Оператор ++ будет применяться к объекту s, вызывая дружественную функцию operator++(Student&).`

`Дружественная функция operator++(Student&) также должна изменить состояние объекта s и вернуть ссылку на него.`

14. В программе описан класс
```cpp
class Student
{
	bool operator<(Student &P);
};
```
**и определены объекты этого класса**
```cpp
Student a,b;
```
**Выполняется операция**
```cpp
cout << a < b;
```
**Каким образом, компилятор будет воспринимать вызов функции-операции?**

`В данном случае, компилятор будет воспринимать вызов оператора сравнения следующим образом:`

`Оператор < будет применяться к объектам a и b, вызывая метод operator<(Student&) внутри класса Student.`

`Метод operator<(Student&) должен вернуть true или false в зависимости от результата сравнения.`

`При выводе булевых значений в консоль они выводятся как 0 или 1`

**15. В программе описан класс**
```cpp
class Student
{
	friend bool operator >(const Person&, Person&)
};
```
**и определены объекты этого класса**
```cpp
Student a,b;
```
**Выполняется операция**
```cpp
cout << a > b;
```
**Каким образом, компилятор будет воспринимать вызов функции-операции?**

`Если оператор > перегружен как дружественная функция, то компилятор будет воспринимать вызов следующим образом:`

`Оператор > будет применяться к объектам a и b, вызывая дружественную функцию operator>(const Student&, Student&).`

`Дружественная функция operator>(const Student&, Student&) также должна вернуть true или false.`

`При выводе булевых значений в консоль они выводятся как 0 или 1`
