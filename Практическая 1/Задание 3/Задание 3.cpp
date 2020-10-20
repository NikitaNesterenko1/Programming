
#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b; 
     
    std::cout << "Введите a" << std::endl;
    std::cin >> a;
    std::cout << "Введите b" << std::endl;
    std::cin >> b;

    std::cout << "Сложение " << a + b << std::endl;
    std::cout << "Вычитание " << a - b << std::endl;
    std::cout << "Умножение " << a * b << std::endl;
    std::cout << "Деление " << a / b << std::endl;

    system("pause");
}

