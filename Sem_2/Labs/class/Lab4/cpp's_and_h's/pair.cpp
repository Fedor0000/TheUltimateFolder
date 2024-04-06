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
