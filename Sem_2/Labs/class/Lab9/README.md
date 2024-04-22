# Лабораторная работа №9 "Обработка исключительных ситуаций."

## Постановка задачи

1. Реализовать класс, перегрузить для него операции, указанные в варианте.
2. Определить исключительные ситуации.
3. Предусмотреть генерацию исключительных ситуаций.

### 7 Вариант:

```txt
Класс-контейнер МНОЖЕСТВО с элементами типа int.
	Реализовать операции:
[]    – доступа по индексу;
int() – определение размера вектора;
*     – пересечение множеств;
--    - удаление элемента из множества.
```

## UML-диаграмма

![uml](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab9/uml.png)

## Код программы

`plurality.h`
```cpp
#pragma once
using namespace std;
class Plurality
{
public:
	Plurality();
	Plurality(unsigned int);
	Plurality(unsigned int s, int k);
	Plurality(const Plurality& a);
	~Plurality();
	unsigned int getCapacity();
	void deleteDubs();
	void pushBack(int);
	int& back();
	int popBack();
	void diet();
	void setSize(unsigned int);
	void setCapacity(unsigned int);
	Plurality& operator=(const Plurality&);
	unsigned int operator ()();
	int& operator[](int);
	Plurality operator+(const int);
	Plurality operator*(Plurality&);
	Plurality& operator--(int);
	Plurality& operator--();
	friend ostream& operator<<(ostream& out, Plurality& a);
	friend istream& operator>>(istream& in, Plurality& a);
private:
	unsigned int capacity; // размер массива
	unsigned int size; // НОМЕР самого последнего элемента
	int* data;
};
```

`plurality.cpp`
```cpp
#pragma once
#include <iostream>
#include <vector>
#include "plurality.h"
using namespace std;
Plurality::Plurality() // пустое множество по умолчанию ёмкость 100
{
	capacity = 100;
	size = 0;
	data = new int[capacity];
	for (int i = 0; i < capacity; i++) data[i] = 0;
}
Plurality::Plurality(unsigned int c) // множество, заполненное нулями, размером c, емкость на 50 больше
{
	capacity = c + 50; // доп ёмкость
	size = c;
	data = new int[capacity];
	for (int i = 0; i < capacity; i++) data[i] = 0;
}
Plurality::Plurality(unsigned int s, int k) // массив заполнен k, размер s, емкость на 50 выше
{
	capacity = s + 50;
	size = s;
	data = new int[capacity];
	for (int i = 0; i < capacity; i++) data[i] = k;
}
Plurality::Plurality(const Plurality& a) // копия имеет доп емкость
{
	capacity = a.size + 50;
	size = a.size;
	data = new int[capacity];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
}
Plurality::~Plurality()
{
	delete[] data;
	data = 0;
}
unsigned int Plurality::getCapacity() // говорит о том, какая емкость в данный момент
{
	return capacity;
}
void Plurality::deleteDubs() // уничтожить дубли
{
	int newSize = 0;
	vector<int> biloUzhe;
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
	Plurality result(biloUzhe.size());
	for (int i = 0; i < biloUzhe.size(); i++) result[i] = biloUzhe[i];
	*this = result;
}
void Plurality::pushBack(int dat) // добавить элемент в конец, на емкость пофик
{
	if (size == capacity)
	{
		int* mas = new int[size + 50];
		for (int i = 0; i < size; i++)
		{
			mas[i] = data[i];
		}
		delete[] data;
		data = mas;
		capacity = size + 50;
		data[size] = dat;
		size++;
	}
	else
	{
		data[size] = dat;
		size++;
	}
}
int& Plurality::back() // ссылка на задницу множества
{
	if (size == 0) throw 4;
	return data[size - 1];
}
int Plurality::popBack() // удалить один элемент сзади
{
	if (size == 0) throw 5;;
	int tmp = data[size - 1];
	data[size-1] = 0;
	size--;
	return tmp;
}
void Plurality::diet() // емкость равна размеру
{
	int* mas = new int[size];
	for (int i = 0; i < size; i++)
	{
		mas[i] = data[i];
	}
	delete[] data;
	data = mas;
	capacity = size;
}
void Plurality::setSize(unsigned int newSize) // устанавливает заданный размер, если меньше начального, лишнее обрезается
{
	if (newSize >= size)
	{
		if (newSize <= capacity) size = newSize;
		else
		{
			int* mas = new int[newSize + 50];
			for (int i = 0; i < size; i++) mas[i] = data[i];
			for (int i = size; i < newSize+50; i++) mas[i] = 0;
			delete[] data;
			data = mas;
			size = newSize;
			capacity = newSize + 50;
		}
	}
	else
	{
		for (int i = newSize; i < size; i++) data[i] = 0;
		size = newSize;
	}
}
void Plurality::setCapacity(unsigned int newCapacity) // устанавливает заданную ёмкость, то что не вошло - теряется
{
	if (newCapacity > capacity)
	{
		int* mas = new int[newCapacity];
		for (int i = 0; i < size; i++) mas[i] = data[i];
		for (int i = size; i < newCapacity; i++) mas[i] = 0;
		delete[] data;
		data = mas;
		capacity = newCapacity;
	}
	else if (newCapacity == capacity) return;
	else
	{
		int* mas = new int[newCapacity];
		for (int i = 0; i < newCapacity; i++) mas[i] = 0;
		for (int i = 0; i < (size<=newCapacity ? size : newCapacity); i++) mas[i] = data[i];
		delete[] data;
		data = mas;
		capacity = newCapacity;
		size = (size <= newCapacity ? size : newCapacity);
	}
}
Plurality& Plurality::operator=(const Plurality& a)
{
	if (this == &a) return *this;
	size = a.size;
	capacity = a.size + 50;
	if (data != 0) delete[] data;
	data = new int[capacity];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
	return *this;
}
unsigned int Plurality::operator()()
{
	return size;
}
int& Plurality::operator[](int index)
{
	if (index < 0) throw 2;
	if (index >= size) throw 3;
	return data[index];
}
Plurality Plurality::operator+(const int k)
{
	Plurality tmp(*this);
	tmp.pushBack(k);
	return tmp;
}
Plurality Plurality::operator*(Plurality& p)
{
	Plurality temper(size);
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
	Plurality temp(newSize);
	for (int i = 0; i < newSize; i++)
	{
		temp[i] = temper[i];
	}
	return temp;
}
Plurality& Plurality::operator--(int)
{
	Plurality old(*this);
	popBack();
	return old;
}
Plurality& Plurality::operator--()
{
	popBack();
	return *this;
}
ostream& operator<<(ostream& out, Plurality& a)
{
	out << "Вывод множества:" << endl;
	if (a() == 0)
	{
		cout << "Пусто.";
	}
	else
	{
		for (int i = 0; i < a(); ++i)
		{
			out << a.data[i] << " ";
		}
	}
	out << endl;
	return out;
}
istream& operator>>(istream& in, Plurality& a)
{
	if (a() == 0) throw 1;
	cout << "Ввод множества: " << endl;
	for (int i = 0; i < a(); ++i)
	{
		cout << "Введите элемент множества: [" << i << "] = ";
		in >> a.data[i];
	}
	cout << endl;
	return in;
}
```

`pluralityE.h` (second realization)
```cpp
#pragma once
using namespace std;
class PluralityE
{
public:
	PluralityE();
	PluralityE(unsigned int);
	PluralityE(unsigned int s, int k);
	PluralityE(const PluralityE& a);
	~PluralityE();
	unsigned int getCapacity();
	void deleteDubs();
	void pushBack(int);
	int& back();
	int popBack();
	void diet();
	void setSize(unsigned int);
	void setCapacity(unsigned int);
	PluralityE& operator=(const PluralityE&);
	unsigned int operator ()();
	int& operator[](int);
	PluralityE operator+(const int);
	PluralityE operator*(PluralityE&);
	PluralityE& operator--(int);
	PluralityE& operator--();
	friend ostream& operator<<(ostream& out, PluralityE& a);
	friend istream& operator>>(istream& in, PluralityE& a);
private:
	unsigned int capacity; // размер массива
	unsigned int size; // НОМЕР самого последнего элемента
	int* data;
};
```

`pluralityE.cpp` (second realization)
```cpp
#pragma once
#include <iostream>
#include <vector>
#include "pluralityE.h"
#include "error.h"
using namespace std;
PluralityE::PluralityE() // пустое множество по умолчанию ёмкость 100
{
	capacity = 100;
	size = 0;
	data = new int[capacity];
	for (int i = 0; i < capacity; i++) data[i] = 0;
}
PluralityE::PluralityE(unsigned int c) // множество, заполненное нулями, размером c, емкость на 50 больше
{
	capacity = c + 50; // доп ёмкость
	size = c;
	data = new int[capacity];
	for (int i = 0; i < capacity; i++) data[i] = 0;
}
PluralityE::PluralityE(unsigned int s, int k) // массив заполнен k, размер s, емкость на 50 выше
{
	capacity = s + 50;
	size = s;
	data = new int[capacity];
	for (int i = 0; i < capacity; i++) data[i] = k;
}
PluralityE::PluralityE(const PluralityE& a) // копия имеет доп емкость
{
	capacity = a.size + 50;
	size = a.size;
	data = new int[capacity];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
}
PluralityE::~PluralityE()
{
	delete[] data;
	data = 0;
}
unsigned int PluralityE::getCapacity() // говорит о том, какая емкость в данный момент
{
	return capacity;
}
void PluralityE::deleteDubs() // уничтожить дубли
{
	int newSize = 0;
	vector<int> biloUzhe;
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
	PluralityE result(biloUzhe.size());
	for (int i = 0; i < biloUzhe.size(); i++) result[i] = biloUzhe[i];
	*this = result;
}
void PluralityE::pushBack(int dat) // добавить элемент в конец, на емкость пофик
{
	if (size == capacity)
	{
		int* mas = new int[size + 50];
		for (int i = 0; i < size; i++)
		{
			mas[i] = data[i];
		}
		delete[] data;
		data = mas;
		capacity = size + 50;
		data[size] = dat;
		size++;
	}
	else
	{
		data[size] = dat;
		size++;
	}
}
int& PluralityE::back() // ссылка на задницу множества
{
	if (size == 0) throw error("Ошибка! В этом множестве нет элементов, не на что давать ссылку!");
	return data[size - 1];
}
int PluralityE::popBack() // удалить один элемент сзади
{
	if (size == 0) throw error("Ошибка! В этом множестве нет элементов, удалять нечего!");;
	int tmp = data[size - 1];
	data[size-1] = 0;
	size--;
	return tmp;
}
void PluralityE::diet() // емкость равна размеру
{
	int* mas = new int[size];
	for (int i = 0; i < size; i++)
	{
		mas[i] = data[i];
	}
	delete[] data;
	data = mas;
	capacity = size;
}
void PluralityE::setSize(unsigned int newSize) // устанавливает заданный размер, если меньше начального, лишнее обрезается
{
	if (newSize >= size)
	{
		if (newSize <= capacity) size = newSize;
		else
		{
			int* mas = new int[newSize + 50];
			for (int i = 0; i < size; i++) mas[i] = data[i];
			for (int i = size; i < newSize+50; i++) mas[i] = 0;
			delete[] data;
			data = mas;
			size = newSize;
			capacity = newSize + 50;
		}
	}
	else
	{
		for (int i = newSize; i < size; i++) data[i] = 0;
		size = newSize;
	}
}
void PluralityE::setCapacity(unsigned int newCapacity) // устанавливает заданную ёмкость, то что не вошло - теряется
{
	if (newCapacity > capacity)
	{
		int* mas = new int[newCapacity];
		for (int i = 0; i < size; i++) mas[i] = data[i];
		for (int i = size; i < newCapacity; i++) mas[i] = 0;
		delete[] data;
		data = mas;
		capacity = newCapacity;
	}
	else if (newCapacity == capacity) return;
	else
	{
		int* mas = new int[newCapacity];
		for (int i = 0; i < newCapacity; i++) mas[i] = 0;
		for (int i = 0; i < (size<=newCapacity ? size : newCapacity); i++) mas[i] = data[i];
		delete[] data;
		data = mas;
		capacity = newCapacity;
		size = (size <= newCapacity ? size : newCapacity);
	}
}
PluralityE& PluralityE::operator=(const PluralityE& a)
{
	if (this == &a) return *this;
	size = a.size;
	capacity = a.size + 50;
	if (data != 0) delete[] data;
	data = new int[capacity];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
	return *this;
}
unsigned int PluralityE::operator()()
{
	return size;
}
int& PluralityE::operator[](int index)
{
	if (index < 0) throw error("Ошибка! Индекс не может быть отрицательным!");
	if (index >= size) throw error("Ошибка! Индекс слишком большой!");
	return data[index];
}
PluralityE PluralityE::operator+(const int k)
{
	PluralityE tmp(*this);
	tmp.pushBack(k);
	return tmp;
}
PluralityE PluralityE::operator*(PluralityE& p)
{
	PluralityE temper(size);
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
	PluralityE temp(newSize);
	for (int i = 0; i < newSize; i++)
	{
		temp[i] = temper[i];
	}
	return temp;
}
PluralityE& PluralityE::operator--(int)
{
	PluralityE old(*this);
	popBack();
	return old;
}
PluralityE& PluralityE::operator--()
{
	popBack();
	return *this;
}
ostream& operator<<(ostream& out, PluralityE& a)
{
	out << "Вывод множества:" << endl;
	if (a() == 0)
	{
		cout << "Пусто.";
	}
	else
	{
		for (int i = 0; i < a(); ++i)
		{
			out << a.data[i] << " ";
		}
	}
	out << endl;
	return out;
}
istream& operator>>(istream& in, PluralityE& a)
{
	if (a() == 0) throw error("Ошибка! Размер множества = 0, невозможно ввести элементы!");
	cout << "Ввод множества: " << endl;
	for (int i = 0; i < a(); ++i)
	{
		cout << "Введите элемент множества: [" << i << "] = ";
		in >> a.data[i];
	}
	cout << endl;
	return in;
}
```

`error.h` (for second realization)
```cpp
#pragma once
#include <string>
#include <iostream>
using namespace std;
class error //класс ошибка
{
	string str;
public:
	error(string s)
	{
		str = s;
	}
	void what()
	{
		cout << str << endl;
	}
};
```

`main.cpp` (first and second realization in one main)
```cpp
#include <iostream>
#include "plurality.h"
#include "pluralityE.h"
#include "error.h"
using namespace std;
void menu()
{
	int method;
	cout << "\nВыберите вариант реализации обработки исключительных ситуаций:\n0. Выйти из программы.\n1. Просто говорить о том, что возникла ошибка.\n2. Говорить о том, какая ошибка возникла (через класс-обработчик).\n3. Проверка операций в штатном режиме.\nВыбранный метод --------> ";
	cin >> method;
	cout << endl;
	switch (method)
	{
	case 0:
	{
		cout << endl << "Выход из программы..." << endl;
		break;
	}
	case 1:
	{
		srand(time(NULL));
		cout << "\nВыберите операцию, в которой произойдет исключительная ситуация:\n1. Ввод в пустое множество.\n2. Отрицательный индекс.\n3. Индекс больше размера.\n4. Получить ссылку на конец множества, но оно пустое.\n5. Удалить один элемент из пустого множества.\nЧтобы ничего не выбирать и вернуться в начало введите несуществующий номер.\nВыбранный метод --------> ";
		cin >> method;
		cout << endl;
		switch (method)
		{
		case 1:
		{
			try
			{
				Plurality pl;
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем ввести в него что-нибудь." << endl;
				cin >> pl;
			}
			catch (int)
			{
				cout << "Произошла ошибка!!!" << endl;
			}
			break;
		}
		case 2:
		{
			try
			{
				Plurality pl;
				for (int i = 0; i < 30; i++) pl.pushBack((rand() % 100));
				pl.deleteDubs();
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем вывести элемент с -4 индексом." << endl;
				cout << pl[-4];
			}
			catch (int)
			{
				cout << "Произошла ошибка!!!" << endl;
			}
			break;
		}
		case 3:
		{
			try
			{
				Plurality pl;
				for (int i = 0; i < 30; i++) pl.pushBack((rand() % 100));
				pl.deleteDubs();
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем вывести элемент с 40 индексом." << endl;
				cout << pl[40];
			}
			catch (int)
			{
				cout << "Произошла ошибка!!!" << endl;
			}
			break;
		}
		case 4:
		{
			try
			{
				Plurality pl;
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем получить ссылку на последний элемент и вывести его." << endl;
				cout << pl.back();
			}
			catch (int)
			{
				cout << "Произошла ошибка!!!" << endl;
			}
			break;
		}
		case 5:
		{
			try
			{
				Plurality pl;
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем удалить элемент из этого множества." << endl;
				--pl;
			}
			catch (int)
			{
				cout << "Произошла ошибка!!!" << endl;
			}
			break;
		}
		default:break;
		}
		menu();
		break;
	}
	case 2:
	{
		srand(time(NULL));
		cout << "\nВыберите операцию, в которой произойдет исключительная ситуация:\n1. Ввод в пустое множество.\n2. Отрицательный индекс.\n3. Индекс больше размера.\n4. Получить ссылку на конец множества, но оно пустое.\n5. Удалить один элемент из пустого множества.\nЧтобы ничего не выбирать и вернуться в начало введите несуществующий номер.\nВыбранный метод --------> ";
		cin >> method;
		cout << endl;
		switch (method)
		{
		case 1:
		{
			try
			{
				PluralityE pl;
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем ввести в него что-нибудь." << endl;
				cin >> pl;
			}
			catch (error e)
			{
				e.what();
			}
			break;
		}
		case 2:
		{
			try
			{
				PluralityE pl;
				for (int i = 0; i < 30; i++) pl.pushBack((rand() % 100));
				pl.deleteDubs();
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем вывести элемент с -4 индексом." << endl;
				cout << pl[-4];
			}
			catch (error e)
			{
				e.what();
			}
			break;
		}
		case 3:
		{
			try
			{
				PluralityE pl;
				for (int i = 0; i < 30; i++) pl.pushBack((rand() % 100));
				pl.deleteDubs();
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем вывести элемент с 40 индексом." << endl;
				cout << pl[40];
			}
			catch (error e)
			{
				e.what();
			}
			break;
		}
		case 4:
		{
			try
			{
				PluralityE pl;
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем получить ссылку на последний элемент и вывести его." << endl;
				cout << pl.back();
			}
			catch (error e)
			{
				e.what();
			}
			break;
		}
		case 5:
		{
			try
			{
				PluralityE pl;
				cout << "Посмотрим, что находится в множестве:" << endl;
				cout << pl << "А теперь попробуем удалить элемент из этого множества." << endl;
				--pl;
			}
			catch (error e)
			{
				e.what();
			}
			break;
		}
		default:break;
		}
		menu();
		break;
	}
	case 3:
	{
		srand(time(NULL));
		Plurality plR;
		for (int i = 0; i < 30; i++) plR.pushBack((rand() % 100));
		plR.deleteDubs();
		cout << "Случайное множество:" << endl << plR;
		cout << "Последний элемент случайного множества: " << plR.back() << endl;
		Plurality plM(10);
		cout << "Множество на десять в ручном режиме: " << endl;
		cin >> plM;
		plM.deleteDubs();
		cout << plM;
		cout << "Элемент по индексу ноль этого множества: " << plM[0] << endl;
		Plurality plpl = plR * plM;
		cout << "Пересечение этих множеств:\n" << plpl;
		cout << "Емкость пересечения: " << plpl.getCapacity() << endl;
		cout << "Размер пересечения: " << plpl() << endl;
		cout << "Из пересечения выпнули последний элемент и посадили его на диету:\n";
		int tmp = plpl.popBack();
		plpl.diet();
		cout << plpl << endl;
		cout << "Теперь емкость пересечения: " << plpl.getCapacity() << endl;
		cout << "Размер пересечения теперь: " << plpl() << endl;
		cout << "Не бойтесь, мы вернули элемент, который выкинули:\n";
		plpl.pushBack(tmp);
		cout << plpl << endl;
		cout << "Теперь емкость пересечения: " << plpl.getCapacity() << endl;
		cout << "Размер пересечения теперь: " << plpl() << endl;
		menu();
		break;
	}
	default:
	{
		menu();
		break;
	}
	cout << endl;
	}
}
int main()
{
	system("chcp 1251 > null");
	menu();
	return 0;
}
```

## Тесты текстом

```txt
<тесты выполнены одним большим запуском>

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 23


Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> -5


Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 1


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 1

Посмотрим, что находится в множестве:
Вывод множества:
Пусто.
А теперь попробуем ввести в него что-нибудь.
Произошла ошибка!!!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 1


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 2

Посмотрим, что находится в множестве:
Вывод множества:
94 93 5 12 69 52 17 76 99 92 10 96 40 65 26 53 90 67 46 20 6 82 23 61 71 18 85
А теперь попробуем вывести элемент с -4 индексом.
Произошла ошибка!!!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 1


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 3

Посмотрим, что находится в множестве:
Вывод множества:
1 21 65 2 98 6 42 22 55 64 14 93 37 13 34 72 28 60 83 99 44 53 69 52 71
А теперь попробуем вывести элемент с 40 индексом.
Произошла ошибка!!!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 1


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 4

Посмотрим, что находится в множестве:
Вывод множества:
Пусто.
А теперь попробуем получить ссылку на последний элемент и вывести его.
Произошла ошибка!!!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 1


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 5

Посмотрим, что находится в множестве:
Вывод множества:
Пусто.
А теперь попробуем удалить элемент из этого множества.
Произошла ошибка!!!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 1


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 0


Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 2


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 1

Посмотрим, что находится в множестве:
Вывод множества:
Пусто.
А теперь попробуем ввести в него что-нибудь.
Ошибка! Размер множества = 0, невозможно ввести элементы!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 2


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 5

Посмотрим, что находится в множестве:
Вывод множества:
Пусто.
А теперь попробуем удалить элемент из этого множества.
Ошибка! В этом множестве нет элементов, удалять нечего!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 2


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 2

Посмотрим, что находится в множестве:
Вывод множества:
0 14 68 4 27 92 93 66 54 80 60 12 21 83 47 81 19 99 98 73 33 44 59 45 22 78 49 6
А теперь попробуем вывести элемент с -4 индексом.
Ошибка! Индекс не может быть отрицательным!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 2


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 4

Посмотрим, что находится в множестве:
Вывод множества:
Пусто.
А теперь попробуем получить ссылку на последний элемент и вывести его.
Ошибка! В этом множестве нет элементов, не на что давать ссылку!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 2


Выберите операцию, в которой произойдет исключительная ситуация:
1. Ввод в пустое множество.
2. Отрицательный индекс.
3. Индекс больше размера.
4. Получить ссылку на конец множества, но оно пустое.
5. Удалить один элемент из пустого множества.
Чтобы ничего не выбирать и вернуться в начало введите несуществующий номер.
Выбранный метод --------> 3

Посмотрим, что находится в множестве:
Вывод множества:
1 35 71 67 17 75 25 97 77 98 99 76 6 8 57 15 41 33 22 52 36 85 69 59 19 83
А теперь попробуем вывести элемент с 40 индексом.
Ошибка! Индекс слишком большой!

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 3

Случайное множество:
Вывод множества:
86 81 18 25 33 8 63 51 42 88 29 23 53 52 48 45 61 91 24 10 22 75 46 93 20 92 7
Последний элемент случайного множества: 7
Множество на десять в ручном режиме:
Ввод множества:
Введите элемент множества: [0] = 33
Введите элемент множества: [1] = 63
Введите элемент множества: [2] = 63
Введите элемент множества: [3] = 33
Введите элемент множества: [4] = 0
Введите элемент множества: [5] = 7
Введите элемент множества: [6] = 7
Введите элемент множества: [7] = 0
Введите элемент множества: [8] = 33
Введите элемент множества: [9] = 1

Вывод множества:
33 63 0 7 1
Элемент по индексу ноль этого множества: 33
Пересечение этих множеств:
Вывод множества:
33 63 7
Емкость пересечения: 53
Размер пересечения: 3
Из пересечения выпнули последний элемент и посадили его на диету:
Вывод множества:
33 63

Теперь емкость пересечения: 2
Размер пересечения теперь: 2
Не бойтесь, мы вернули элемент, который выкинули:
Вывод множества:
33 63 7

Теперь емкость пересечения: 52
Размер пересечения теперь: 3

Выберите вариант реализации обработки исключительных ситуаций:
0. Выйти из программы.
1. Просто говорить о том, что возникла ошибка.
2. Говорить о том, какая ошибка возникла (через класс-обработчик).
3. Проверка операций в штатном режиме.
Выбранный метод --------> 0


Выход из программы...

```

## Тесты скриншоты

![Скриншот номер 1](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab9/screen/1.png)

![Скриншот номер 2](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab9/screen/2.png)

![Скриншот номер 3](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab9/screen/3.png)

![Скриншот номер 4](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab9/screen/4.png)

![Скриншот номер 5](https://github.com/Fedor0000/TheUltimateFolder/blob/main/Sem_2/Labs/class/Lab9/screen/5.png)

## Ответы на вопросы

**1. Что представляет собой исключение в С++?**

`Исключение — это механизм реагирования на исключительные ситуации, такие как ошибки, которые возникают во время выполнения программы. Исключение представляет собой временный объект любого типа, который используется для сигнализации об ошибке.`

**2. На какие части исключения позволяют разделить вычислительный процесс? Достоинства такого подхода?**

`Исключения позволяют разделить вычислительный процесс на часть, где может возникнуть ошибка, и часть, где происходит обработка ошибки. Это упрощает управление ошибками, делая код более читаемым и поддерживаемым.`

**3. Какой оператор используется для генерации исключительной ситуации?**

`Для генерации исключения используется оператор throw.`

**4. Что представляет собой контролируемый блок? Для чего он нужен?**

`Контролируемый блок — это блок кода, обозначенный ключевым словом try, в котором выполняются инструкции, потенциально способные вызвать исключение. Он нужен для определения тех участков кода, где должна происходить обработка исключений.`

**5. Что представляет собой секция-ловушка? Для чего она нужна?**

`Секция-ловушка — это блок кода, следующий за контролируемым блоком, обозначенный ключевым словом catch, который содержит параметр, передающий информацию об исключении и инструкции для его обработки. Она нужна для обработки исключений, сгенерированных в контролируемом блоке.`

**6. Какие формы может иметь спецификация исключения в секции ловушке? В каких ситуациях используются эти формы?**

`Спецификация исключения в секции ловушке может быть точной, когда указывается конкретный тип исключения, или общей, когда используется многоточие (...) для перехвата любого типа исключения. Точная форма используется для обработки конкретных исключений, а общая — когда точный тип исключения неизвестен или не важен.`

**7. Какой стандартный класс можно использовать для создания собственной иерархии исключений?**

`Для создания собственной иерархии исключений можно использовать стандартный класс exception, который определен в заголовочном файле <exception>.`

**8. Каким образом можно создать собственную иерархию исключений?**

`Собственную иерархию исключений можно создать, наследуя классы от стандартного класса exception или других производных от него классов исключений.`

**9. Если спецификация исключений имеет вид: void f1() throw(int, double); то какие исключения может прождать функция f1()?**

`Если спецификация исключений имеет вид void f1() throw(int, double);, то функция f1 может генерировать исключения типов int и double`

**10. Если спецификация исключений имеет вид: void f1() throw(); то какие исключения может прождать функция f1()?**

`Если спецификация исключений имеет вид void f1() throw();, то функция f1 не должна генерировать никаких исключений.`

**11. В какой части программы может генерироваться исключение?**

`Исключение может генерироваться в любой части программы, где используется оператор throw, но обычно это происходит в функциях или методах, которые выполняют операции, способные вызвать ошибки.`

**12. Написать функцию, которая вычисляет площадь треугольника по трем сторонам (формула Герона). Функцию реализовать в 4 вариантах:**
- без спецификации исключений;
- со спецификацией throw();
- с конкретной спецификацией с подходящим стандартным исключением;
- спецификация с собственным реализованным исключением.

$p=\frac{a+b+c}{2}$

$S=\sqrt{p(p-a)(p-b)(p-c)}$

```cpp
#include <iostream>
#include <exception>
class error //класс ошибка
{
    std::string str;
public:
    error(std::string s) { str = s; }
    void what() {std::cout << str << std::endl;}
};

double geron1(double a, double b, double c) // герон, не создающий исключений
{
    double p = (a + b + c) / 2.0;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
}

double geron2(double a, double b, double c) // герон, создающий целочисленные исключения
{
    if (!((a > 0) && (b > 0) && (c > 0))) throw 1; // проверка сторон на адекватность
    if (!((a + b > c) && (b + c > a) && (a + c > b))) throw 2; // проверка сторон на то, что они стороны треугольника
    double p = (a + b + c) / 2.0;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
}

double geron3(double a, double b, double c) // герон, создающий стандартные исключения
{
    if (!((a > 0) && (b > 0) && (c > 0))) throw std::exception(); // проверка сторон на адекватность
    if (!((a + b > c) && (b + c > a) && (a + c > b))) throw std::exception(); // проверка сторон на то, что они стороны треугольника
    double p = (a + b + c) / 2.0;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
}

double geron4(double a, double b, double c) // герон, создающий собственные исключения
{
    if (!((a > 0) && (b > 0) && (c > 0))) throw error("ОШИБКА! Стороны не адекватны!"); // проверка сторон на адекватность
    if (!((a + b > c) && (b + c > a) && (a + c > b))) throw error("ОШИБКА! Данные числа не стороны треугольника вовсе!"); // проверка сторон на то, что они стороны треугольника
    double p = (a + b + c) / 2.0;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
}
```
