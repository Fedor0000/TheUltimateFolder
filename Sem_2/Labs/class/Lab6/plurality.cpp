// 👍🏼 - Он убирает кракозябры.
#pragma once
#include <iostream>
#include <vector>
#include "plurality.h"
using namespace std;
Iterator Iterator::operator++()
{
	this->elem++;
	return *this;
}
Iterator Iterator::operator--()
{
	this->elem--;
	return *this;
}
Iterator Iterator::operator++(int)
{
	Iterator result(elem);
	this->elem++;
	return result;
}
Iterator Iterator::operator--(int)
{
	Iterator result(elem);
	this->elem--;
	return result;
}
Plurality::Plurality(int s, int k)
{
	size = s;
	data = new int[size];
	for (int i = 0; i < size; i++) data[i] = k;
	beg.elem = &data[0];
	end.elem = &data[size];
}
//конструктор копирования
Plurality::Plurality(const Plurality& a)
{
	size = a.size;
	data = new int[size];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
	beg = a.beg;
	end = a.end;
}
Plurality::~Plurality()
{
	delete[] data;
	data = 0;
}
void Plurality::deleteDubs()
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
	this->beg = &this->data[0];
	this->end = &this->data[biloUzhe.size()];
}
//операция присваивания
Plurality& Plurality::operator=(const Plurality& a)
{
	if (this == &a) return *this;
	size = a.size;
	if (data != 0) delete[] data;
	data = new int[size];
	for (int i = 0;i < size;i++) data[i] = a.data[i];
	beg = a.beg;
	end = a.end;
	return *this;
}
int Plurality::operator()()
{
	return size;
}
int& Plurality::operator[](int index)
{
	if (index < size) return data[index];
	else { cout << "\nОшибка! Индекс больше размера множества."; exit(1); }
}
Plurality Plurality::operator+(const int k)
{
	Plurality temp(size);
	for (int i = 0;i < size;++i)
		temp.data[i] += data[i] + k;
	return temp;
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
ostream& operator<<(ostream& out, Plurality& a)
{
	out << "Вывод множества:" << endl;
	for (int i = 0; i < a(); ++i)
	{
		out << a.data[i] << " ";
	}
	out << endl;
	return out;
}
istream& operator>>(istream& in, Plurality& a)
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