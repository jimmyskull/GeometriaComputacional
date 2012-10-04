# -*- encoding: utf-8 -*-
import sys
from random import randint

rnd = lambda: randint(-100, +100)

n = int(sys.argv[1])
print(n)
for i in range(n):
	print(rnd(), rnd())
