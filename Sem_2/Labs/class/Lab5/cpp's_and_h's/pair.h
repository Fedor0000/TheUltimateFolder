/*
Базовый класс:
ПАРА_ЧИСЕЛ (PAIR)
Первое_число (first) - int
Второе_число (second) – int
Определить методы проверки на равенство и операцию перемножения полей.
Реализовать операцию вычитания пар по формуле (a,b)-(c,d)=(a-b,c-d)
Создать производный класс ПРОСТАЯ_ДРОБЬ(RATIONAL), с полями Числитель и
Знаменатель. Переопределить операцию вычитания и определить операции сложения
и умножения простых дробей
*/
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