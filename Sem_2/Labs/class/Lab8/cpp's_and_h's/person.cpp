// 👍🏻
#pragma once
#include <iostream>
#include <string>
#include "person.h"
#include "event.h"
using namespace std;
Person::Person()
{
	name = "";
	age = 0;
}
Person::~Person() {}
Person::Person(string N, int A)
{
	name = N;
	age = A;
}
Person::Person(const Person& person)
{
	name = person.name;
	age = person.age;
}
void Person::setName(string N)
{
	name = N;
}
void Person::setAge(int A)
{
	age = A;
}
Person& Person::operator=(const Person& p)
{
	if (&p == this) return *this;
	name = p.name;
	age = p.age;
	return *this;
}
void Person::HandleEvent(const TEvent& e)
{
	if (e.what == evMessage) //событие-сообщение
	{
		switch (e.command)
		{
		case cmNames: cout << "Имя = " << getName() << endl; break;
		}
	}
}
void Person::Show()
{
	cout << "\nИмя: " << name;
	cout << "\nВозраст: " << age;
	cout << "\n";
}
void Person::Input()
{
	cout << "\nВведите имя: "; cin >> name;
	cout << "\nВведите возраст: "; cin >> age;
}