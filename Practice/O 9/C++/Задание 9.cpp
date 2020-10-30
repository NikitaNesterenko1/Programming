
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double h1, h2, m1, m2, a;
    cout << "h1 m1: "; cin >> h1 >> m1;
    cout << "h2 m2: "; cin >> h2 >> m2;
    h1 = h1 * 60;
    h2 = h2 * 60;
    a = (h1 - h2) + (m1 - m2);
    if (a <= 15) {
        cout << "Встреча состоится";
    }
    else {
        cout << "Встреча не состоится";
    }
}