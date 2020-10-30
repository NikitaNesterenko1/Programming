

#include <iostream>
using namespace std;
int main()

{
    setlocale(LC_ALL, "Russian");
    double m, a, b;
    char c;
    cout << "ввод чисел"; cin >> a >> c >> b;
    if (c == '*') {
        cout << "m="; m = a * b;
    }
    else if (c == '/') {
        cout << "m="; m = a / b;
    }
    else if (c == '+') {
        cout << "m="; m = a + b;
    }
    else if (c == '-') {
        cout << "m="; m = a - b;
    }
    else {
        cout << "не поддержимаемая операция";
        return 0;
    }
    cout <<  "m=" << m ;
}


