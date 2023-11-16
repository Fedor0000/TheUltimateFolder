#include <iostream>
using namespace std;
int main()
{
	int a, n;
	int s = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		a = i;
		for (int g = i; g < 2*i; g++)
		{
			a = a * (g + 1);
		}
		s = s + a;
	}
	cout << s << endl;
	return 0;
}