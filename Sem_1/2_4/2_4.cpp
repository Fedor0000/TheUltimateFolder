#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	if ((n > 3) && (n % 2 != 0))
	{
		int spaces = n / 2;
		int stars = 1;
		for (int i = 0; i<(n +1 )/ 2; i++)
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
			stars += 2;
			cout << endl;
		}		
	}
	else
	{
		cout << "Число не соответствует условию" << endl;
	}
	return 0;
}