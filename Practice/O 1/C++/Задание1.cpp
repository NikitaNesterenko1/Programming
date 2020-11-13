

#include <iostream>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");

	int a = 5;
	int b = 6;
	cout << ((a > b) ? b : a);
}

