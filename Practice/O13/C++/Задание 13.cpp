
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int n, i; bool s = false;
	cout << "n="; cin >> n;
	for (i = 2; (i <= sqrt(n)); i++) {
		if (n % i == 0) {
			s = true;
			break;
		}
	}
	if(s)
			cout << "Составное";
		else 
			cout << "Простое";
	return 0;


}

