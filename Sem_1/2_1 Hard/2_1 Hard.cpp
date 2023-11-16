#include <iostream>
using namespace std;
int main()
{
	int n, a;
	int b = 0;
	cin >> n;
	if (n >= 2)
	{
		for (int i = 0; i < n; i++)
		{
			cin >> a;
			b = b + a;
		}
		cout << b;
	}
	else
	{
		cout << "Для получения суммы чисел нужно хотя бы два числа";
	}
	return 0;
}