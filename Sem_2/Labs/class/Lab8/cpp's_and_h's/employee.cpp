// 👍🏻
#pragma once
#include <iostream>
#include <string>
#include "employee.h"
using namespace std;
Employee::Employee() : Person()
{
	salary = 0;
	positionAtWork = "";
}
Employee::~Employee() {}
Employee::Employee(string N, int A, double S, string P) : Person(N, A)
{
	salary = S;
	positionAtWork = P;
}
Employee::Employee(const Employee& E)
{
	name = E.name;
	age = E.age;
	salary = E.salary;
	positionAtWork = E.positionAtWork;
}
void Employee::setSalary(double S)
{
	salary = S;
}
void Employee::setPositionAtWork(string P)
{
	positionAtWork = P;
}
Employee& Employee::operator=(const Employee& E)
{
	if (&E == this) return *this;
	name = E.name;
	age = E.age;
	salary = E.salary;
	positionAtWork = E.positionAtWork;
	return *this;
}
void Employee::Show()
{
	cout << "\nИмя: " << name;
	cout << "\nВозраст: " << age;
	cout << "\nЗаработная плата: " << salary;
	cout << "\nДолжность: " << positionAtWork;
	cout << "\n";
}
void Employee::Input()
{
	cout << "\nВведите имя: "; cin >> name;
	cout << "\nВведите возраст: "; cin >> age;
	cout << "\nВведите заработную плату: "; cin >> salary;
	cout << "\nВведите должность: "; cin >> positionAtWork;
}