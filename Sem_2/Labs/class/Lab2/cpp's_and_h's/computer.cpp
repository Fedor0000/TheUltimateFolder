#pragma once
#include "computer.h"
#include <iostream>
#include <string>
using namespace std;
Computer::Computer()
{
	processor = "";
	ramCapacity = 0;
	hddCapacity = 0;
	cout << "Был вызван конструктор без параметров для объекта " << this << endl;
}
Computer::Computer(string P, int R, int H)
{
	processor = P;
	ramCapacity = R;
	hddCapacity = H;
	cout << "Был вызван конструктор с параметрами для объекта " << this << endl;
}
Computer::Computer(const Computer& t)
{
	processor = t.processor;
	ramCapacity = t.ramCapacity;
	hddCapacity = t.hddCapacity;
	cout << "Был вызван конструктор копирования для объекта " << this << endl;
}
Computer::~Computer()
{
	cout << "Был вызван деструктор для объекта " << this << endl;
}
string Computer::getProcessor()
{
	return processor;
}
int Computer::getRamCapacity()
{
	return ramCapacity;
}
int Computer::getHddCapacity()
{
	return hddCapacity;
}
void Computer::setProcessor(string P)
{
	processor = P;
}
void Computer::setRamCapacity(int R)
{
	ramCapacity = R;
}
void Computer::setHddCapacity(int H)
{
	hddCapacity = H;
}
void Computer::show()
{
	cout << "Процессор: " << processor << endl;
	cout << "Объем оперативной памяти (в гигабайтах): " << ramCapacity << endl;
	cout << "Объем жёсткого диска (в гигабайтах): " << hddCapacity << endl;
}
