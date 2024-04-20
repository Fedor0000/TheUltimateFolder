// 👍🏻 - он убирает сами знаете что
#pragma once
#include <string>
#include <iostream>
using namespace std;
class error //класс ошибка
{
	string str;
public:
	error(string s)
	{
		str = s;
	}
	void what()
	{
		cout << str << endl;
	}
};