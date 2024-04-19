// 👍🏻
#pragma once
#include "person.h"
using namespace std;
class Employee : public Person
{
public:
	Employee();
	~Employee();
	void Show();
	void Input();
	Employee(string, int, double, string);
	Employee(const Employee&);
	double getSalary() {return salary;}
	string getPositionAtWork() {return positionAtWork;}
	void setSalary(double);
	void setPositionAtWork(string);
	Employee& operator=(const Employee&);
protected:
	double salary;
	string positionAtWork;
};