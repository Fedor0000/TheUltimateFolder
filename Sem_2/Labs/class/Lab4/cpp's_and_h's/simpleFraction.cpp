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
	cout << "¬ведите числитель ";
	in >> l.first;
	cout << "¬ведите знаменатель ";
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