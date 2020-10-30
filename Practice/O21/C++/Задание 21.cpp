
#include <iostream>
using namespace std;

double BMI(double weight, double height) {
	return weight / (height * height);
}

void printBMI(double bmi) {
	if (bmi < 18.5)
		cout << "Underweight";
	else if (18.5 <= bmi && bmi < 25.0)
		cout << "Normal";
	else if (25.0 <= bmi && bmi < 30.0)
		cout << "Overweight";
	else
		cout << "Obesity";
}

int main()
{
	setlocale(LC_ALL, "ru");
	int weight, height;
	cout << "Введите вес и рост "; cin >> weight >> height;

	printBMI(BMI(weight, (double) height / 100));
}
