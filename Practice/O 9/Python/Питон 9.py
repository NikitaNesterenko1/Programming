MINUTES_IN_HOUR = 60

print('Введите 2 времени в формате \"ЧЧ:ММ\" каждое с новой строки')

a, b = [int(x) for x in input().split(sep=':')]
c, d = [int(x) for x in input().split(sep=':')]
h1, m1 = map(int, input().split(sep=':'))
h2, m2 = map(int, input().split(sep=':'))

a = 60 * a + b
c = 60 * c + d
m1 = MINUTES_IN_HOUR * h1 + m1
m2 = MINUTES_IN_HOUR * h1 + m2

if abs(a - c) > 15:
    print('Встреча не состоится')
else:
    print('Встреча состоится')