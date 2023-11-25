#include <iostream>
using namespace std;
int main()
{
	int n;	
	float min, chislo, max;
	cout << "Enter number of elements of subsequence of positive numbers: ";
	cin >> n;
	cout << endl;
	cin >> chislo; // Чтобы мусор не мешал, мин и макс в начале это первое число текущей последовательности
	min = chislo;
	max = chislo;
	for (int i = 1; i < n; i++)
	{
		cin >> chislo;
		if (chislo > max) { max = chislo; }
		if (chislo < min) { min = chislo; }
	}
	cout << endl;
	cout << "Min + Max = " << min + max << endl;
	return 0;
}