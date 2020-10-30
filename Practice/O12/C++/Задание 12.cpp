#include <iostream>
using namespace std;

int main()
{
	int N, f=1; 
	cout << "N = ";
	cin >> N; 
	if (N >= 0)
	{
		for (int i = 1; i <= N; i++)
		{
			 f *= i; 
		}
		cout << "N=" << f;
	}
	else
	{
		cout << "Error: N < 0"; 
	}
}