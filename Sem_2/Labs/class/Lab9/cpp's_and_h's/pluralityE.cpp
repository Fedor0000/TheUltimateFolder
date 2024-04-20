// 👍🏼 - Он убирает кракозябры.
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