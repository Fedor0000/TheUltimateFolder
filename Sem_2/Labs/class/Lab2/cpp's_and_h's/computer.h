#pragma once
#include <iostream>
#include <string>
using namespace std;
class Computer
{
	string processor;
	int ramCapacity;
	int hddCapacity;
public:
	Computer();
	Computer(string, int, int);
	Computer(const Computer&);
	~Computer();
	string getProcessor();
	void setProcessor(string);
	int getRamCapacity();
	void setRamCapacity(int);
	int getHddCapacity();
	void setHddCapacity(int);
	void show();
};