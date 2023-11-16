#include <iostream>
using namespace std;
int main()
{
	int n, a;
	int b = 1;
	cin >> n;
	if (n > 1)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> a;
			b = b * a;
		}
		cout << b;
	}
	else
	{
		cout << "Для получения произведения чисел нужно ввести хотя бы два числа";
	}
	return 0;
}