
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, c;
	cout << "a="; cin >> a;
	cout << "b="; cin >> b;
	c = pow(a, b);
	cout << "c=" << c;
}

