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
	cout << "��� ������ ����������� ��� ���������� ��� ������� " << this << endl;
}
Computer::Computer(string P, int R, int H)
{
	processor = P;
	ramCapacity = R;
	hddCapacity = H;
	cout << "��� ������ ����������� � ����������� ��� ������� " << this << endl;
}
Computer::Computer(const Computer& t)
{
	processor = t.processor;
	ramCapacity = t.ramCapacity;
	hddCapacity = t.hddCapacity;
	cout << "��� ������ ����������� ����������� ��� ������� " << this << endl;
}
Computer::~Computer()
{
	cout << "��� ������ ���������� ��� ������� " << this << endl;
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
	cout << "���������: " << processor << endl;
	cout << "����� ����������� ������ (� ����������): " << ramCapacity << endl;
	cout << "����� ������� ����� (� ����������): " << hddCapacity << endl;
}