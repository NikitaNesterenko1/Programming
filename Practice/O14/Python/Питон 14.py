n = int(input("введите  число.\n"))
x = 0

if n >= 1:
    x += 1

while n > 1:
    n //= 2
    x += 1

print(x)