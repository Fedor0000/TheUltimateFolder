# Лабораторная работа №7 "Шаблоны классов."

## Постановка задачи

1. Определить шаблон класса-контейнера (см. лабораторную работу №6).
2. Реализовать конструкторы, деструктор, операции ввода-вывода, операцию присваивания.
3. Перегрузить операции, указанные в варианте.
4. Инстанцировать шаблон для стандартных типов данных (int, float, double).
5. Написать тестирующую программу, иллюстрирующую выполнение операций для контейнера, содержащего элементы стандартных типов данных.
6. Реализовать пользовательский класс (см. лабораторную работу №3).
7. Перегрузить для пользовательского класса операции ввода-вывода.
8. Перегрузить операции необходимые для выполнения операций контейнерного класса.
9. Инстанцировать шаблон для пользовательского класса.
10. Написать тестирующую программу, иллюстрирующую выполнение операций для контейнера, содержащего элементы пользовательского класса.

### 7 Вариант:

Класс- контейнер МНОЖЕСТВО с элементами типа int.
Реализовать операции:
- [] – доступа по индексу;
- () – определение размера вектора;
- *  – пересечение множеств;
Пользовательский класс Money для работы с денежными суммами. Число должно быть представлено двумя полями: типа long для рублей и типа int для копеек.
Дробная часть числа при выводе на экран должна быть отделена от целой части запятой.

## UML-диаграмма

![](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab7/uml.png)

## Код программы

`plurality.cpp`
```cpp
#pragma once
#include <iostream>
#include <vector>
using namespace std;
template <class T>
class Plurality
{
public:
	Plurality(int s, T k);
	//конструктор с параметрами
	Plurality(const Plurality<T>& a);
	//деструктор
	~Plurality();
	void deleteDubs();
	Plurality& operator=(const Plurality<T>&);
	int operator ()();
	T& operator[](int);
	Plurality operator+(const int);
	Plurality operator*(Plurality<T>&);
	friend istream& operator>> <> (istream& in, Plurality<T>& a);
	friend ostream& operator<< <> (ostream& out, Plurality<T>& a);
private:
	int size;
	T* data;
};


template <class T>
Plurality<T>::Plurality(int s, T k)
{
	size = s;
	data = new T[size];
	for (int i = 0; i < size; i++) data[i] = k;
}
//конструктор копирования
template <class T>
Plurality<T>::Plurality(const Plurality<T>& a)
{
	size = a.size;
	data = new T[size];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
}
template <class T>
Plurality<T>::~Plurality()
{
	delete[] data;
	data = 0;
}
template <class T>
void Plurality<T>::deleteDubs()
{
	int newSize = 0;
	vector<T> biloUzhe;
	biloUzhe.push_back(data[0]);
	for (int i = 1; i < size; i++)
	{
		bool yest = false;
		for (int j = 0; j < biloUzhe.size(); j++)
		{
			if (data[i] == biloUzhe[j])
			{
				yest = true;
				break;
			}
		}
		if (!yest) biloUzhe.push_back(data[i]);
	}
	Plurality<T> result (biloUzhe.size(), biloUzhe[0]);
	for (int i = 0; i < biloUzhe.size(); i++) result[i] = biloUzhe[i];
	*this = result;
}
//операция присваивания
template <class T>
Plurality<T>& Plurality<T>::operator=(const Plurality<T>& a)
{
	if (this == &a) return *this;
	size = a.size;
	if (data != 0) delete[] data;
	data = new T[size];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
	return *this;
}
template <class T>
int Plurality<T>::operator()()
{
	return size;
}
template <class T>
T& Plurality<T>::operator[](int index)
{
	if (index < size) return data[index];
	else { cout << "\nОшибка! Индекс больше размера множества."; exit(1); }
}
template <class T>
Plurality<T> Plurality<T>::operator+(const int k)
{
	Plurality<T> temp(size, data[0]);
	for (int i = 0; i < size; ++i) temp.data[i] = data[i] + k;
	return temp;
}
template <class T>
Plurality<T> Plurality<T>::operator*(Plurality<T>& p)
{
	Plurality<T> temper(size);
	int newSize = 0;
	int it = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < p(); j++)
		{
			if (data[i] == p.data[j])
			{
				temper[it++] = data[i];
				newSize++;
				break;
			}
		}
	}
	Plurality<T> temp(newSize);
	for (int i = 0; i < newSize; i++)
	{
		temp[i] = temper[i];
	}
	return temp;
}
template <class T>
istream& operator>> (istream& in, Plurality<T>& a)
{
	cout << "Ввод множества: " << endl;
	for (int i = 0; i < a(); ++i)
	{
		cout << "Введите элемент множества: [" << i << "] = ";
		in >> a.data[i];
	}
	cout << endl;
	return in;
}
template <class T>
ostream& operator<< (ostream& out, Plurality<T>& a)
{
	out << "Вывод множества:" << endl;
	for (int i = 0; i < a(); ++i)
	{
		out << a.data[i] << " ";
	}
	out << endl;
	return out;
}
```

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
	long long int getRubles()
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
	bool operator==(const Money&);
	Money& operator++(); // префиксная
	Money& operator--(); // префиксная
	Money operator++(int); //постфиксная
	Money operator--(int); //постфиксная
	Money operator+(const Money&);
	Money operator+(int);
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
bool Money::operator==(const Money& a)
{
	if ((rubles == a.rubles) && (kopecks == a.kopecks)) return true;
	return false;
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
	long long int temp = rubles;
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
Money Money::operator+(int a)
{
	int allKopSum = a * 100;
	int allKopecks = kopecks + rubles * 100;
	int buf = allKopecks + allKopSum;
	Money summa;
	summa.kopecks = buf % 100;
	summa.rubles = buf / 100;
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
	long long int buf;
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
#include "plurality.cpp"
#include "money.h"
using namespace std;
int main()
{
	system("chcp 1251 > null");
	//инициализация, ввод и вывод значений вектора
	Plurality<int> AA(5, 0);
	cin >> AA;
	AA.deleteDubs();
	cout << AA << endl;
	//инициализация и вывод значений вектора
	Plurality<int> BB(10, 1);
	cout << "Второе множество: десять элементов по умолчанию:\n" << BB << endl;
	//операция присваивания
	BB = AA;
	cout << "В это множество скопировали первое:\n" << BB << endl;
	//доступ по индексу
	int ind;
	cout << "Введите индекс: ";
	cin >> ind;
	cout << "Элемент первого множества по индексу:\n" << AA[ind] << endl;
	//получение длины вектора
	cout << "Размер первого множества = " << AA() << endl;
	//операция сложения с константой
	BB = AA + 10;
	BB.deleteDubs();
	cout << "B = A + 10\n" << BB << endl;
	cout << endl << "Одна денежная сумма: " << endl;
	Money denga;
	cin >> denga;
	cout << denga << endl;
	cout << "Увеличим сумму на К, введите К: ";
	int k;
	cin >> k;
	Money p;
	p = denga + k;
	cout << p << endl;

	cout << "Множество из пяти денег:\n";
	Plurality<Money> A(5, p);
	cin >> A;
	A.deleteDubs();
	cout << A << endl;
	cout << "Множество из десяти увеличенных денег из примера с одной денежной суммой:\n";
	Plurality<Money> B(10, p);
	cout << B << endl;
	B = A;
	cout << "В это множество скопировали первое:\n";
	cout << B << endl;
	cout << "Введите индекс: ";
	cin >> ind;
	cout << "Элемент множества по индексу: " << A[ind] << endl;
	cout << "Размер первого множества: " << A() << endl;
	return 0;
}
```

## Тесты текстом

```cpp
/*
1)
Ввод множества:
Введите элемент множества: [0] = 32
Введите элемент множества: [1] = 34
Введите элемент множества: [2] = 65
Введите элемент множества: [3] = 23
Введите элемент множества: [4] = 3

Вывод множества:
32 34 65 23 3

Второе множество: десять элементов по умолчанию:
Вывод множества:
1 1 1 1 1 1 1 1 1 1

В это множество скопировали первое:
Вывод множества:
32 34 65 23 3

Введите индекс: 2
Элемент первого множества по индексу:
65
Размер первого множества = 5
B = A + 10
Вывод множества:
42 44 75 33 13


Одна денежная сумма:
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 4
Введите копейки без рублей: 123
5,23
Увеличим сумму на К, введите К: 18
23,23
Множество из пяти денег:
Ввод множества:
Введите элемент множества: [0] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 23
Введите копейки без рублей: 34
Введите элемент множества: [1] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): -76
Введите копейки без рублей: -45
Введите элемент множества: [2] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 0
Введите копейки без рублей: 23
Введите элемент множества: [3] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 0
Введите копейки без рублей: 2
Введите элемент множества: [4] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 0
Введите копейки без рублей: 23

Вывод множества:
23,34 -76,45 0,23 0,02

Множество из десяти увеличенных денег из примера с одной денежной суммой:
Вывод множества:
23,23 23,23 23,23 23,23 23,23 23,23 23,23 23,23 23,23 23,23

В это множество скопировали первое:
Вывод множества:
23,34 -76,45 0,23 0,02

Введите индекс: 1
Элемент множества по индексу: -76,45
Размер первого множества: 4


2)
Ввод множества:
Введите элемент множества: [0] = 34
Введите элемент множества: [1] = -65
Введите элемент множества: [2] = 0
Введите элемент множества: [3] = 87
Введите элемент множества: [4] = 0

Вывод множества:
34 -65 0 87

Второе множество: десять элементов по умолчанию:
Вывод множества:
1 1 1 1 1 1 1 1 1 1

В это множество скопировали первое:
Вывод множества:
34 -65 0 87

Введите индекс: 1
Элемент первого множества по индексу:
-65
Размер первого множества = 4
B = A + 10
Вывод множества:
44 -55 10 97


Одна денежная сумма:
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): -5
Введите копейки без рублей: -545
-10,45
Увеличим сумму на К, введите К: 20
9,55
Множество из пяти денег:
Ввод множества:
Введите элемент множества: [0] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 67
Введите копейки без рублей: 54
Введите элемент множества: [1] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 0
Введите копейки без рублей: 0
Введите элемент множества: [2] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): -98
Введите копейки без рублей: -5
Введите элемент множества: [3] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 45
Введите копейки без рублей: 65
Введите элемент множества: [4] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 34
Введите копейки без рублей: 340

Вывод множества:
67,54 0,00 -98,05 45,65 37,40

Множество из десяти увеличенных денег из примера с одной денежной суммой:
Вывод множества:
9,55 9,55 9,55 9,55 9,55 9,55 9,55 9,55 9,55 9,55

В это множество скопировали первое:
Вывод множества:
67,54 0,00 -98,05 45,65 37,40

Введите индекс: 0
Элемент множества по индексу: 67,54
Размер первого множества: 5


3)
Ввод множества:
Введите элемент множества: [0] = -575
Введите элемент множества: [1] = 35735
Введите элемент множества: [2] = 3
Введите элемент множества: [3] = -5
Введите элемент множества: [4] = 0

Вывод множества:
-575 35735 3 -5 0

Второе множество: десять элементов по умолчанию:
Вывод множества:
1 1 1 1 1 1 1 1 1 1

В это множество скопировали первое:
Вывод множества:
-575 35735 3 -5 0

Введите индекс: 1
Элемент первого множества по индексу:
35735
Размер первого множества = 5
B = A + 10
Вывод множества:
-565 35745 13 5 10


Одна денежная сумма:
Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 0
Введите копейки без рублей: 900
9,00
Увеличим сумму на К, введите К: 1
10,00
Множество из пяти денег:
Ввод множества:
Введите элемент множества: [0] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 54
Введите копейки без рублей: 4
Введите элемент множества: [1] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 54
Введите копейки без рублей: 45
Введите элемент множества: [2] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 5
Введите копейки без рублей: 4
Введите элемент множества: [3] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 54
Введите копейки без рублей: 4
Введите элемент множества: [4] = Введите рубли без копеек (если вы вводите отрицательное число, вводите и рубли и копейки со знаком минус): 65
Введите копейки без рублей: 5

Вывод множества:
54,04 54,45 5,04 65,05

Множество из десяти увеличенных денег из примера с одной денежной суммой:
Вывод множества:
10,00 10,00 10,00 10,00 10,00 10,00 10,00 10,00 10,00 10,00

В это множество скопировали первое:
Вывод множества:
54,04 54,45 5,04 65,05

Введите индекс: 3
Элемент множества по индексу: 65,05
Размер первого множества: 4
*/
```

## Тесты скриншоты

![Скриншот номер 1](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab7/screen/1.png)
![Скриншот номер 2](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab7/screen/2.png)
![Скриншот номер 3](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab7/screen/3.png)

## Ответы на вопросы

**1. В чем смысл использования шаблонов?**

`Шаблоны в программировании используются для повышения переиспользования кода, снижения его сложности и увеличения гибкости.`

**2. Каковы синтаксис/семантика шаблонов функций?**

`Синтаксис шаблонов функций начинается с ключевого слова template, за которым следуют угловые скобки с параметрами шаблона. Семантика заключается в создании функций, не зависящих от конкретных типов.`

**3. Каковы синтаксис/семантика шаблонов классов?**

`Шаблоны классов позволяют определить классы с объектами неизвестного типа на этапе написания кода. Синтаксис включает ключевое слово template и параметры шаблона в угловых скобках.`

**4. Что такое параметры шаблона функции?**

`Параметры шаблона функции - это формальные имена, вынесенные в шаблон, которые заменяются на конкретные типы при инстанцировании шаблона.`

**5. Перечислите основные свойства параметров шаблона функции.**

`Основные свойства параметров шаблона функции включают: уникальность имен, неопускание идентификаторов в прототипе, возможность пустого списка параметров, и требование одного типа для всех экземпляров аргумента шаблона.`

**6. Как записывать параметр шаблона?**

`Параметр шаблона записывается в угловых скобках после ключевого слова template, и каждому параметру должно предшествовать слово class или typename.`

**7. Можно ли перегружать параметризованные функции?**

`Да, можно перегружать параметризованные функции, но они должны отличаться списком входных параметров.`

**8. Перечислите основные свойства параметризованных классов.**

`Параметризованные классы описывают семейство классов с одним или более неопределенным формальным параметром, и каждый класс отличается значениями этих параметров.`

**9. Все ли компонентные функции параметризованного класса являются параметризованными?**

`Не все компонентные функции параметризованного класса обязательно являются параметризованными.`

**10. Являются ли дружественные функции, описанные в параметризованном классе, параметризованными?**

`Дружественные функции, описанные в параметризованном классе, не обязательно являются параметризованными.`

**11. Могут ли шаблоны классов содержать виртуальные компонентные функции?**

`Да, шаблоны классов могут содержать виртуальные компонентные функции.`

**12. Как определяются компонентные функции параметризованных классов вне определения шаблона класса?**

`Компонентные функции параметризованных классов определяются вне определения шаблона класса с указанием списка параметров шаблона после имени класса.`

**13. Что такое инстанцирование шаблона?**

`Инстанцирование шаблона - это процесс создания конкретного экземпляра из шаблона путем замены параметров шаблона на конкретные типы или значения.`

**14. На каком этапе происходит генерирование определения класса по шаблону?**

`Генерирование определения класса по шаблону происходит на этапе компиляции, когда компилятор заменяет параметры шаблона на фактические типы.`
