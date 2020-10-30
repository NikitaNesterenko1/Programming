
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int n;
	cout << "Введите значение n "; cin >> n;
	string k = "";
	cout << "Введите значение k "; cin >> k;
	for (int i = 0; i < k.size(); i++) {
		for (int j = 0; j < n; j++) {
			cout << k[i];
		}
		cout << ' ';
	}
}

