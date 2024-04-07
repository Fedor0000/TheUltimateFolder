#pragma once
#include "pair.h"
class SimpleFraction : public Pair
{
public:
	SimpleFraction();
	~SimpleFraction();
	void Show();
	SimpleFraction(int, int);
	SimpleFraction(const SimpleFraction&);
	SimpleFraction operator-(const SimpleFraction&);
	SimpleFraction operator+(const SimpleFraction&);
	SimpleFraction operator*(const SimpleFraction&);
	friend istream& operator>>(istream& in, SimpleFraction& l);
	friend ostream& operator<<(ostream& out, const SimpleFraction& l);
};