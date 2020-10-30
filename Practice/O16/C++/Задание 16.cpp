#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");

	int n;
	cout << "Введите колличество билетов Суслика: " << endl;
	cin >> n;
	string tickets;
	string symbols = "";
	cout << "Введите номера билетов через пробел: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> tickets;
		if ((tickets[0] == 'a') && (tickets[4] == '5') && (tickets[5] == '5') && (tickets[6] == '6') && (tickets[7] == '6') && (tickets[8] == '1')) {
			symbols = symbols + tickets + ' ';
		}
	}
	if (symbols == "")
		cout << -1;
	else
		cout << "Билеты Суслика:" << endl << symbols;
}
