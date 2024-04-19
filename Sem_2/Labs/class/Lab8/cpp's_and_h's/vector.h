// 👍🏻
#pragma once
#include "event.h"
#include "object.h"
class Vector
{
public:
	Vector();
	Vector(int);
	~Vector();
	void Add();
	void Del();
	void Show();
	int operator()();
	virtual void HandleEvent(const TEvent& e);
protected:
	Object** beg;
	int size;
	int cur;
};