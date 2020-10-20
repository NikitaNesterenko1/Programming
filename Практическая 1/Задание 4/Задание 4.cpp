#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b, c;

    std::cout << "Введите a" << std::endl;
    std::cin >> a;
    std::cout << "Введите b" << std::endl;
    std::cin >> b;

    std::cout << "a=" << b << "\n";
    std::cout << "b=" << a << "\n";
}

using namespace std;