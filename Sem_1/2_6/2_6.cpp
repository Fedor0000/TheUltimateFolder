#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	if (n > 2)
	{
		int spaces = 1;
		int stars = n;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j < spaces;j++)
			{
				cout << " ";
			}
			spaces = spaces++;
			for (int j = 1; j <= stars; j++)
			{
				cout << "*";
			}
			stars -= 1;
			cout << endl;
		}
	}
	else
	{
		cout << "Число должно быть больше двух" << endl;
	}
	return 0;
}