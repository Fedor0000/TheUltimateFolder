#include <iostream>
#include "pair.h"
#include "simpleFraction.h"
using namespace std;
void f1(Pair& c)
{
	int f;
	cout << "������� ����� ������ ����� ����: ";
	cin >> f;
	c.setFirst(f);
	cout << c;
}
Pair f2()
{
	int i, j;
	cout << "������� ��� ����� ����� ������ ��� �������� �����: ";
	cin >> i >> j;
	SimpleFraction l(i, j);
	return l;
}
void main()
{
	setlocale(LC_ALL, "Russian");
	Pair a;
	cin >> a;
	cout << a;
	cout << "������ ����� ���� �: " << a.getFirst() << endl << "������ ����� ���� �: " << a.getSecond() << endl;
	if (a.isEqual()) cout << "���� A ������� �� ���������� �����." << endl;
	else cout << "����� � ���� A ������." << endl;
	cout << "��� ��� �����, ���� ����������� ����� � ���� A: " << a.product() << endl;
	cout << "���� B. ����������� � ����������� � � �:" << endl;
	int tv, mg;
	cout << "������� ���������:" << endl << "� = ";
	cin >> tv;
	cout << "� = ";
	cin >> mg;
	Pair b(tv, mg);
	cout << b;
	if (a == b) cout << "���� ��������� ���������." << endl;
	else cout << "���� �� ��������� ���������." << endl;
	cout << "��������� ��� �� �������: (�_������, �_������) - (�_������, �_������) = (�_������ - �_������, �_������, �_������):" << endl << a - b;
	a = b;
	cout << "������ � = �, ����� ������ �: " << endl;
	cout << a;
	SimpleFraction c, d;
	cin >> c;
	cin >> d;
	cout << c << endl;
	cout << d;
	cout << "������ �� ����� � ����� �:" << endl << c - d;
	cout << "������ ����� � � �:" << endl << c + d;
	cout << "���������� ����� � � �:" << endl << c * d;
	cout << "������� ������ ����� ����� � � ��������� �� � ����:" << endl;
	f1(c);
	cout << "�������� �����, �� ������� ��� ����: " << endl;
	a = f2();
	cout << a;
}
/*
		�����:
1)
������� ������ ����� ����: 6
������� ������ ����� ����: 6
������ ����� ����: 6
������ ����� ����: 6
������ ����� ���� �: 6
������ ����� ���� �: 6
���� A ������� �� ���������� �����.
��� ��� �����, ���� ����������� ����� � ���� A: 36
���� B. ����������� � ����������� � � �:
������� ���������:
� = 89
� = -1
������ ����� ����: 89
������ ����� ����: -1
���� �� ��������� ���������.
��������� ��� �� �������: (�_������, �_������) - (�_������, �_������) = (�_������ - �_������, �_������, �_������):
������ ����� ����: 0
������ ����� ����: 90
������ � = �, ����� ������ �:
������ ����� ����: 89
������ ����� ����: -1
������� ��������� 1
������� ����������� 10
������� ��������� 1
������� ����������� 15
  1
----
 10

  1
----
 15
������ �� ����� � ����� �:
  1
----
 30
������ ����� � � �:
  5
----
 30
���������� ����� � � �:
  1
-----
 150
������� ������ ����� ����� � � ��������� �� � ����:
������� ����� ������ ����� ����: 23
������ ����� ����: 23
������ ����� ����: 10
�������� �����, �� ������� ��� ����:
������� ��� ����� ����� ������ ��� �������� �����: 34 56
������ ����� ����: 34
������ ����� ����: 56

2)
������� ������ ����� ����: -4
������� ������ ����� ����: 67
������ ����� ����: -4
������ ����� ����: 67
������ ����� ���� �: -4
������ ����� ���� �: 67
����� � ���� A ������.
��� ��� �����, ���� ����������� ����� � ���� A: -268
���� B. ����������� � ����������� � � �:
������� ���������:
� = -4
� = 67
������ ����� ����: -4
������ ����� ����: 67
���� ��������� ���������.
��������� ��� �� �������: (�_������, �_������) - (�_������, �_������) = (�_������ - �_������, �_������, �_������):
������ ����� ����: -71
������ ����� ����: -71
������ � = �, ����� ������ �:
������ ����� ����: -4
������ ����� ����: 67
������� ��������� 1
������� ����������� 10
������� ��������� -1
������� ����������� 15
  1
----
 10

 -1
----
 15
������ �� ����� � ����� �:
  5
----
 30
������ ����� � � �:
  1
----
 30
���������� ����� � � �:
 -1
-----
 150
������� ������ ����� ����� � � ��������� �� � ����:
������� ����� ������ ����� ����: 10
������ ����� ����: 10
������ ����� ����: 10
�������� �����, �� ������� ��� ����:
������� ��� ����� ����� ������ ��� �������� �����: -12 52
������ ����� ����: -12
������ ����� ����: 52

3)
������� ������ ����� ����: 87
������� ������ ����� ����: 34
������ ����� ����: 87
������ ����� ����: 34
������ ����� ���� �: 87
������ ����� ���� �: 34
����� � ���� A ������.
��� ��� �����, ���� ����������� ����� � ���� A: 2958
���� B. ����������� � ����������� � � �:
������� ���������:
� = 9
� = 999
������ ����� ����: 9
������ ����� ����: 999
���� �� ��������� ���������.
��������� ��� �� �������: (�_������, �_������) - (�_������, �_������) = (�_������ - �_������, �_������, �_������):
������ ����� ����: 53
������ ����� ����: -990
������ � = �, ����� ������ �:
������ ����� ����: 9
������ ����� ����: 999
������� ��������� 56
������� ����������� 127
������� ��������� 4
������� ����������� 13
 56
-----
 127

  4
----
 13
������ �� ����� � ����� �:
 220
------
 1651
������ ����� � � �:
1236
------
 1651
���������� ����� � � �:
 224
------
 1651
������� ������ ����� ����� � � ��������� �� � ����:
������� ����� ������ ����� ����: 233
������ ����� ����: 233
������ ����� ����: 127
�������� �����, �� ������� ��� ����:
������� ��� ����� ����� ������ ��� �������� �����: 2222 1111
������ ����� ����: 2222
������ ����� ����: 1111
*/