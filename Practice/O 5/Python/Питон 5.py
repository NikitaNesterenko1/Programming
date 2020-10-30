# 5. Падение объекта
import sys

g = 9.8
x0, V0, t = map(float, input().split())
a = g

x = x0 + V0 * t - (a * t * t) / 2
s = x - x0

print(s)