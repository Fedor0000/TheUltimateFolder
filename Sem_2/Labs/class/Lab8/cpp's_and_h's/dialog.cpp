// 👍🏻
#pragma once
#include <iostream>
#include <string>
#include "dialog.h"
#include "event.h"
#include "vector.h"
#include "object.h"
using namespace std;
Dialog::Dialog() : Vector() {EndState = 0;}
Dialog::~Dialog() {}
void Dialog::GetEvent(TEvent& event)
{
	string OpInt = "+-s/qmz";
	string str;
	string param;
	char code;
	cout << '>';
	cin >> str; code = str[0];
	if (OpInt.find(code) < INT64_MAX) // так как str.find(string) выводит UINT64_MAX, если не находит подстроку, а UINT64_MAX > INT64_MAX
	{
		event.what = evMessage;
		switch (code)
		{
		case 'm': event.command = cmMake;     break; //создать группу
		case '+': event.command = cmAdd;      break; //добавить объект в группу
		case '-': event.command = cmDel;      break; //удалить объект из группы
		case 's': event.command = cmShow;     break; //просмотр группы
		case 'q': event.command = cmQuit;     break; //конец работы
		case '/': event.command = cmNames;    break; // вывести все имена
		case 'z': event.command = cmOneName;  break; // вывести все имена
		}
		if (str.length() > 1)
		{
			param = str.substr(1, str.length() - 1);
			int A = atoi(param.c_str());
			event.a = A;
		}
	}
	else event.what = evNothing;
}
int Dialog::Execute()
{
	TEvent event;
	do
	{
		EndState = 0;
		GetEvent(event); //получить событие
		HandleEvent(event); //обработать событие
	}
	while (!Valid());
	return EndState;
}
int Dialog::Valid()
{
	if (EndState == 0) return 0;
	else return 1;
}
void Dialog::ClearEvent(TEvent& event)
{
	event.what = evNothing;//пустое событие
}
void Dialog::EndExec()
{
	EndState = 1;
}
void Dialog::HandleEvent(TEvent& event)
{
	if (event.what == evMessage)
	{
		switch (event.command)
		{
		case cmMake: //создание группы
		{
			size = event.a; //размер группы
			if (event.a <= 0)
			{
				cout << "Введен неадекватный размер!" << endl;
				break;
			}
			beg = new Object * [size];
			cur = 0;
			ClearEvent(event);
			break;
		}
		case cmAdd://добавление
		{
			Add();
			ClearEvent(event);
			break;
		}
		case cmDel: //удаление
		{
			Del();
			ClearEvent(event);
			break;
		}
		case cmShow: //просмотр
		{
			Show();
			ClearEvent(event);
			break;
		}
		case cmQuit: //выход
		{
			EndExec();
			ClearEvent(event);
			break;
		}
		case cmNames: // вывод имен
		{
			Vector::HandleEvent(event);
			ClearEvent(event);
			break;
		}
		case cmOneName: // вывод имени по номеру
		{
			if ((event.a > cur)||(event.a <=0))
			{
				cout << "Введен неадекватный номер!" << endl;
				break;
			}
			Object** p = beg;
			for (int i = 0; i < event.a-1; i++) p++;
			cout << "Имя элемента с номером " << event.a << endl;
			TEvent e;
			e.what = evMessage;
			e.command = cmNames;
			(*p)->HandleEvent(e);
			ClearEvent(event);
			break;
		}
		default:
		{
			ClearEvent(event);
			break;
		}
		}
	};
}