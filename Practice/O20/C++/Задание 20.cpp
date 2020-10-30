#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    int money = 0;
    int k = 0;
    cout << "Введите сумму: "; cin >> money;
    cout << "Введите количество видов напитков: "; cin >> k;
    string *drinks = new string[k];
    int *price = new int[k];
    int *volume = new int[k];
    for (int i = 0; i < k; i++) {
        cout << "Введите напиток: "; cin >> drinks[i] >> price[i] >> volume[i];
    }
    int *buy = new int[k];
    int *number = new int[k];
    int v = 0;
    int sum = 0;
    // сделать расчет
    for (int i = 0; i < k; i++) {
        buy[i] = i;
        number[i] = i;
        v += volume[i];
        sum += price[i];
    }

    for (int i = 0; i < k; i++) {
        cout << drinks[buy[i]] << " " << number[i] << " " << endl;
    }
    cout << v << endl;
    cout << sum << endl;
}