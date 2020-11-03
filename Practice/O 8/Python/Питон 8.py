print(eval(input('Введите выражение\n')))
print(eval(input('Через пробел введите вещественное число, затем оператор и вещественное число. Пример: \"6 * 4\".\n')))


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