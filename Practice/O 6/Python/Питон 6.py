import math

print('Введите три вещественных числа квадратного трёхчлена, каждый с новой строки.')
print("Введите 3 вещественных числа, каждое в отдельной строке.")

a = int(input())
b = int(input())
c = int(input())

if a == 0:
    if b == 0:
        print('Корней нет.')
        print("Корней нет.")
    else:
        print('x =', -c / b)
        print("x =", -c / b)
else:
    d = b**2 - 4*a*c
    if d < 0:
        print('Не найдено действительных корней')
        print("Не найдено действительных корней")
    elif d == 0:
        print('x =', -b/(2*a))
        print("x =", -b/(2*a))
    else:
        d_sqrt = math.sqrt(d)
        x_one = (-b + d_sqrt) / (2 * a)
        x_two = (-b - d_sqrt) / (2 * a)
        print('x1 =', x_one,'\nx2 =', x_two)
        print("x1 =", x_one,"\nx2 =", x_two)