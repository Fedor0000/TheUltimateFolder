#pragma once
#include <string>
#include <iostream>
using namespace std;
class Pair
{
public:
	Pair();
	virtual ~Pair();
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
