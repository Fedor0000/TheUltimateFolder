// 👍🏻 - лайк, не иначе
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "money.h"
using namespace std;
int makeFile(const char* f_name) // создать файл
{
	fstream stream(f_name, ios::out | ios::trunc); //открыть для записи
	if (!stream) return -1; //ошибка открытия файла
	int n;
	Money p;
	cout << "Введите число записей: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> p; //ввод атрибутов объекта из стандартного потока
		stream << p << "\n"; //запись объекта в файловый поток
	}
	stream.close(); //закрыть поток
	return n; //вернуть количество записанных объектов
}
int printFile(const char* f_name) // распечатать содержимое файла
{
	fstream stream(f_name, ios::in);//открыть для чтения
	if (!stream) return -1;//ошибка открытия файла
	Money p; int i = 0;
	while (stream >> p)
	{
		cout << p << "\n";
		i++;
	}
	stream.close();
	return i;
}
int delFile(const char* f_name, int k) // удалить по номеру k
{
	fstream temp("temp", ios::out); //открыть для записи
	fstream stream(f_name, ios::in); //открыть для чтения
	if (!stream) return -1; //ошибка открытия файла
	int i = 0; Money p;
	while (stream >> p) //пока нет конца файла выполняем чтение объекта
	{
		//если прочитан признак конца файла,то выход из цикла
		if (stream.eof()) break;
		i++;
		//если номер объекта не равен k, то записываем его во вспомогательный файл
		if (i != k) temp << p;
	}
	//закрыть файлы
	stream.close(); temp.close();
	remove(f_name); //удалить старый файл
	rename("temp", f_name); // переименовать temp
	return i; //количество прочитанных
}
int addFile(const char* f_name, int k, Money pp) // добавить элемент на позицию k в файле
{
	fstream temp("temp", ios::out); //открыть для записи
	fstream stream(f_name, ios::in); //открыть для чтения
	if (!stream)return -1; //ошибка открытия файла
	Money p; int i = 0, l = 0;
	while (stream >> p)
	{
		if (stream.eof()) break;
		i++;
		if (i == k)
		{
			temp << pp; //записать в temp новую запись
			l++;
		}
		temp << p;
	}
	stream.close(); temp.close();
	remove(f_name);
	rename("temp", f_name);
	return l; //количество добавленных
}
int addEnd(const char* f_name, Money pp) // запись элемента в конец файла
{
	fstream stream(f_name, ios::app); //открыть для добавления
	if (!stream) return -1; //ошибка открытия файла
	stream << pp; //записать новую запись
	return 1;
}
int changeFile(const char* f_name, int k, Money pp) // изменить элемент с номером k на указанный
{
	fstream temp("temp", ios::out); //открыть для записи
	fstream stream(f_name, ios::in); //открыть для чтения
	if (!stream) return -1; //ошибка открытия файла
	Money p; int i = 0, l = 0;
	while (stream >> p)
	{
		if (stream.eof()) break;
		i++;
		if (i == k)
		{
			temp << pp;
			l++;
		}
		else temp << p;
	}
	stream.close(); temp.close();
	remove(f_name);
	rename("temp", f_name);
	return l; //количество измененных элементов
}
int delAllExceptPPFile(const char* f_name, Money pp) // удалить всё, что не равно pp
{
	fstream temp("temp", ios::out); //открыть для записи
	fstream stream(f_name, ios::in); //открыть для чтения
	if (!stream) return -1; //ошибка открытия файла
	Money p; int i = 0, l = 0;
	while (stream >> p)
	{
		if (stream.eof()) break;
		i++;
		if (p == pp)
		{
			temp << p;
			l++;
		}
	}
	stream.close(); temp.close();
	remove(f_name);
	rename("temp", f_name);
	return l; //количество оставшихся элементов
}
int decreaseAllPPFile(const char* f_name, Money pp) // уменьшить всё, что равно pp
{
	fstream temp("temp", ios::out); //открыть для записи
	fstream stream(f_name, ios::in); //открыть для чтения
	if (!stream) return -1; //ошибка открытия файла
	Money p; int i = 0, l = 0;
	while (stream >> p)
	{
		if (stream.eof()) break;
		i++;
		if (p == pp)
		{
			temp << (p/2);
			l++;
		}
		else temp << p;
	}
	stream.close(); temp.close();
	remove(f_name);
	rename("temp", f_name);
	return l; //количество измененных элементов
}
int addKRecsToBegOfFile(const char* f_name, int K) // добавить K элементов в начало файла
{
	fstream temp("temp", ios::out); //открыть для записи
	fstream stream(f_name, ios::in); //открыть для чтения
	if (!stream) return -1; //ошибка открытия файла
	Money p;
	for (int i = 0; i < K; i++)
	{
		cin >> p;
		temp << p;
	}
	while (stream >> p)
	{
		if (stream.eof()) break;
		temp << p;
	}
	stream.close(); temp.close();
	remove(f_name);
	rename("temp", f_name);
	return K;
}