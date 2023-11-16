#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	if (n > 2)
	{
		int spaces = n-1;
		int stars = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < spaces;j++)
			{
				cout << " ";
			}
			spaces = spaces--;
			for (int j = 0; j < stars; j++)
			{
				cout << "*";
			}
			stars += 1;
			cout << endl;
		}
	}
	else
	{
		cout << "Число должно быть больше двух" << endl;
	}
	return 0;
}