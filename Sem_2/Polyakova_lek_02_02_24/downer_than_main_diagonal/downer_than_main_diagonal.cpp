// Заполнить двумерный массив: все элементы, которые выше главной диагонали, равны НУЛЮ, все элементы на главной диагонали, и диагоналей, находящихся ниже и параллельно ей заполняются цифрами от ОДНОГО до ДЕВЯТИ.
#include <iostream>
using namespace std;
int main()
{
	const int n = 11;
	int numbers;
	int a[n][n] = {0};
	for (int i = 0; i < n; i++)
	{
		numbers = 1;
		for (int j = n-1; j >= 0; j--)
		{
			if (j <= i)
			{
				a[i][j] = numbers;
				numbers++;
				if (numbers == 10) numbers = 1;
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