// Заполнить двумерный квадратный массив: элементы, которые одновременно выше главной и побочной диагоналей равны 0, остальные 1.
#include <iostream>
using namespace std;
int main()
{
	const int n = 11;
	int a[n][n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 1;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((j >= (i + 1)) && (j < (n - i - 1)))
			{
				a[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}