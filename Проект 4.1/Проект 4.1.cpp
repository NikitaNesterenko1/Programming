#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b, c;

    std::cout << "Введите a" << std::endl;
    std::cin >> a;
    std::cout << "Введите b" << std::endl;
    std::cin >> b;
    

    std::cout << "c=" << a << "\n";
    
    std::cout << "Введите c" << std::endl;
    std::cin >> c;

    std::cout << "b=" << c << "\n";

    std::cout << "a=" << b << "\n";
}