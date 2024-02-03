// Сортировка методом выбора
#include <iostream>
using namespace std;
int main()
{
	const int n = 20;
	int a[n];
	for (int i = 0; i < n; i++) a[i] = rand() % 301 - 150;
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	cout << endl;
	for (int i = 0; i < n - 1; i++)
	{
		int imin = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[imin]) imin = j;
		}
		int tmp = a[imin];
		a[imin] = a[i];
		a[i] = tmp;
	}
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	return 0;
}