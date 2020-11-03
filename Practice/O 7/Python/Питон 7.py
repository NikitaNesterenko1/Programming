a = b = c = 0.0
inp = int(input())
if inp == 1:
    print("Введите три пары вещественных чисел. Первое число x, второе y.")
    x1, y1 = [float(x) for x in input().split()]
    x2, y2 = [float(x) for x in input().split()]
    x3, y3 = [float(x) for x in input().split()]
    print("Введите длины сторон треугольника.")
    a = float(input())
    b = float(input())
    c = float(input())
elif inp == 2:
    print("Введите три пары вещественных чисел \n" + 
        "числа в паре . Первое число x, второе y.", sep='')
    x1, y1 = map(float, input().split())
    x2, y2 = map(float, input().split())
    x3, y3 = map(float, input().split())

    a = length(x1, y1, x2, y2)
    b = length(x2, y2, x3, y3)
    c = length(x3, y3, x1, y1)
elif inp == 2:
    print("Введите стороны треугольинка")
    a = float(input())
    b = float(input())
    c = float(input())

p = (a + b + c) / 2
S = math.sqrt(p * (p - a) * (p - b) * (p - c))