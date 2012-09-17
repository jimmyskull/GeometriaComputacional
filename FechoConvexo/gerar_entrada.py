# -*- encoding: utf-8 -*-

from random import randint

rnd = lambda: randint(-100, +100)

n = 100
print(n)
for i in range(n):
	print(rnd(), rnd())
