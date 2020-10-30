

#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, c, x, D, x1, x2;

	cout << "a="; cin >> a;

	cout << "b="; cin >> b;

	cout << "c="; cin >> c;

	D = (b * b) - (4 * a * c);

	if (a == 0) {

		x1 = (-c / b);


		cout << "x1=" << x1 << "\n";
	}
	else {
		if (D > 0) {
			x1 = (-b - sqrt(D)) / (2 * a);

			x2 = (-b + sqrt(D)) / (2 * a);

			cout << "x1=" << x1 << "\n";

			cout << "x2=" << x2 << "\n";// цыкал в цыкле при создании двух корней 
		}
		else
			if (D == 0) {

				x1 = b / 2;

				cout << "x1=" << x1 << "\n";// один корень 
			}
			else
				if (D < 0) {

					cout << "Любое число х";// нет корней  (любое значение х)
				}
	}

}

