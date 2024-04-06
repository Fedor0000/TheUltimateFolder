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