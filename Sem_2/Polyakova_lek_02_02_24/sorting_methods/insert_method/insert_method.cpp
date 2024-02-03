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
		for (int j = i + 1; (j > 0) && (a[j-1] > a[j]); j--)
		{
			int tmp = a[j];
			a[j] = a[j-1];
			a[j-1] = tmp;
		}
	}
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	return 0;
}