#include <iostream>
using namespace std;

const string PATTERN = "a???55661";

string check(string ticket) {
	for (int i = 0; i < PATTERN.size(); i++) {
		if ('?' != PATTERN[i] && ticket[i] != PATTERN[i]) {
			return "";
		}
	}
	return ticket + ' ';
}

int main() {
	setlocale(LC_ALL, "ru");

	int n;
	cout << "Введите колличество билетов Суслика: " << endl;
	cin >> n;
	string ticket;
	string symbols = "";
	cout << "Введите номера билетов через пробел: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> ticket;
		symbols += check(ticket);
	}
	if (symbols == "")
		cout << -1;
	else
		cout << "Билеты Суслика:" << endl << symbols;
}
