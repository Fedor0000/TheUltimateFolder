#include <iostream>
using namespace std;
int main()
{
	int n;
	int a = 0;
	cin >> n;
	if (n <= 0)
	{
		cout << "Натуральные числа больше нуля!!!";
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			a = a + i;
		}
		cout << a;
	}
	return 0;
}