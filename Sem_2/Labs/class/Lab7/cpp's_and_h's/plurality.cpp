// 👍🏻 - он убирает кракозябры
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