/*
	 	Постановка задачи
1. Реализовать определение нового класса. Для демонстрации работы с объектами написать главную функцию. Продемонстрировать разные способы создания объектов и массивов объектов.
2. Структура - пара - структура с двумя полями, которые обычно имеют имена first и second. Требуется реализовать тип данных с помощью такой структуры.Во всех заданиях должны присутствовать:
	a.метод инициализации Init (метод должен контролировать значения аргументов на корректность);
	b.ввод с клавиатуры Read;
	c.вывод на экран Show.
3. Реализовать внешнюю функцию make тип(), где тип - тип реализуемой структуры.Функция должна получать значения для полей структуры как параметры функции и возвращать структуру как результат. При передаче ошибочых параметров следует выводить сообщение и заканчивать работу.

	7 Вариант:
Линейное уравнение у=Ax+В. Поле first - дробное число, коэффициент А, поле second - дробное число, коэффициент B. Реализовать метод function(double x) - вычисление значения у для заданного х.
*/
#include <iostream>
#include "equation.h"
using namespace std;
equation make_equation(double F, double S)
{
	equation t;
	t.Init(F, S);
	return t;
}
int main()
{
	setlocale(LC_ALL, "en_US"); // ðóññêèé ëîêàëü ëîìàåò ôóíêöèþ ïðåîáðàçîâàíèÿ ñòðîê â äàáë
	double iks;

	cout << "Regular variable:" << endl;
	equation A;
	equation B;
	A.Init(3.0, 2.2);
	A.Show();
	cout << "y = A * 4 + B = " << A.Function(4) << endl;
	B.Read();
	B.Show();
	cout << "x = ";
	cin >> iks;
	cout << endl << "y = " << B.first << " * " << iks << " + " << B.second << " = " << B.Function(iks) << endl;

	cout << "Dynamical variable:" << endl;
	equation* C = new equation;
	C->Init(2.0, 5);
	C->Show();
	cout << "x = ";
	cin >> iks;
	cout << endl << "y = " << B.first << " * " << iks << " + " << B.second << " = " << B.Function(iks) << endl;
	delete C;

	cout << "Three elemental static array:" << endl;
	equation mas[3];
	double iksMas[3];
	for (int i = 0; i < 3; i++) mas[i].Read();
	for (int i = 0; i < 3; i++) mas[i].Show();
	cout << "Enter x quotients for three equations:" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "x" << i + 1 << " = ";
		cin >> iksMas[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cout << endl << "y = " << mas[i].first << " * " << iksMas[i] << " + " << mas[i].second << " = " << mas[i].Function(iksMas[i]) << endl;
	}

	cout << "N elemental dynamical array:" << endl;
	int N;
	cout << "N = ";
	cin >> N;
	cout << endl;

	equation* p_mas = new equation[N];
	double* iksMasD = new double[N];
	for (int i = 0; i < N; i++) p_mas[i].Read();
	for (int i = 0; i < N; i++) p_mas[i].Show();
	cout << "Enter x quotients for N equations::" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "x" << i + 1 << " = ";
		cin >> iksMasD[i];
	}
	for (int i = 0; i < N; i++)
	{
		cout << endl << "y = " << p_mas[i].first << " * " << iksMasD[i] << " + " << p_mas[i].second << " = " << p_mas[i].Function(iksMasD[i]) << endl;
	}
	delete[] p_mas;
	delete[] iksMasD;

	cout << "Using function make_equation(a, b):" << endl;
	double y; double z;
	cout << "A = ";
	cin >> y;
	cout << "B = ";
	cin >> z;
	equation F = make_equation(y, z);
	cout << "Output:" << endl;
	F.Show();
	return 0;
}
/*
		ТЕСТЫ
1)
Regular variable:
A = 3
B = 2.2
y = A * 4 + B = 14.2
Enter number A: 5
Enter number B: 5.5
A = 5
B = 5.5
x = -7.6

y = 5 * -7.6 + 5.5 = -32.5
Dynamical variable:
A = 2
B = 5
x = 6.6

y = 5 * 6.6 + 5.5 = 38.5
Three elemental static array:
Enter number A: 7.3
Enter number B: 3.3
Enter number A: 0.0
Enter number B: 5.5
Enter number A: 3.2
Enter number B: -7
A = 7.3
B = 3.3
A = 0
B = 5.5
A = 3.2
B = -7
Enter x quotients for three equations:
x1 = 9.5
x2 = -8.0
x3 = 7.7

y = 7.3 * 9.5 + 3.3 = 72.65

y = 0 * -8 + 5.5 = 5.5

y = 3.2 * 7.7 + -7 = 17.64
N elemental dynamical array:
N = 2

Enter number A: 6.6
Enter number B: 4.4
Enter number A: -3.0
Enter number B: 0
A = 6.6
B = 4.4
A = -3
B = 0
Enter x quotients for N equations::
x1 = 0
x2 = 3.3

y = 6.6 * 0 + 4.4 = 4.4

y = -3 * 3.3 + 0 = -9.9
Using function make_equation(a, b):
A = 3.3
B = 5.5
Output:
A = 3.3
B = 5.5


2)
Regular variable:
A = 3
B = 2.2
y = A * 4 + B = 14.2
Enter number A: rtrttttrr
According to you rtrttttrr - is a number?
C:\Users\Ôåäîð\Desktop\Á\Èíôîðìàòèêà\Ëàáû\1_class\Lab1\x64\Debug\Lab1.exe (ïðîöåññ 13108) çàâåðøèë ðàáîòó ñ êîäîì 1.
Íàæìèòå ëþáóþ êëàâèøó, ÷òîáû çàêðûòü ýòî îêíî:


3)
Regular variable:
A = 3
B = 2.2
y = A * 4 + B = 14.2
Enter number A: 9999
Enter number B: 99999
A = 9999
B = 99999
x = 9

y = 9999 * 9 + 99999 = 189990
Dynamical variable:
A = 2
B = 5
x = 5

y = 9999 * 5 + 99999 = 149994
Three elemental static array:
Enter number A: 0
Enter number B: 0
Enter number A: 0
Enter number B: 0
Enter number A: 0
Enter number B: 0
A = 0
B = 0
A = 0
B = 0
A = 0
B = 0
Enter x quotients for three equations:
x1 = 0
x2 = 0
x3 = 0

y = 0 * 0 + 0 = 0

y = 0 * 0 + 0 = 0

y = 0 * 0 + 0 = 0
N elemental dynamical array:
N = 1

Enter number A: 23
Enter number B: 3.3
A = 23
B = 3.3
Enter x quotients for N equations::
x1 = 3

y = 23 * 3 + 3.3 = 72.3
Using function make_equation(a, b):
A = 3.3
B = 5.5
Output:
A = 3.3
B = 5.5
*/
