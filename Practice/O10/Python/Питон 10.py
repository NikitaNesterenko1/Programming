print("Введите сумму")
s, l1, r1, l2, r2 = [int(x) for x in input().split()]
s, l1, r1, l2, r2 = map(int, input().split())
success = True

i = l1
j = r2
x1 = l1
x2 = 0

if (i + j < s):
    i = min(r1, s-j)
else:
    j = max(l2, s-i)
if x1 + r2 < s:
   
    x2 = r2

if (i + j < s):
    i = min(r1, s-j)

    if s > r1 + x2:
        print("Нет таких иксов")
        success = False
    else:
        x1 = s - r2
else:
    j = max(l2, s-i)

    if s < l1 + l2:
        print("Нет таких иксов")
        success = False
    else:
        x2 = s - x1

if i + j == s:
    print("x1 =", min(i, j), "\nx2 =", max(i, j))
else:
    print("Нет таких x")
if success:
    print("x1 = {}\nx2 = {}".format(x1, x2)) 