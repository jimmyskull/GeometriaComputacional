# -*- encoding: utf-8 -*-

area2 = lambda a,b,c: a[0] * b[1] - a[1] * b[0] +\
					  a[1] * c[0] - a[0] * c[1] +\
					  b[0] * c[1] - b[1] * c[0]
lefton = lambda a,b,c: area2(a, b, c) >= 0

def ler():
	l = ()
	for i in range(int(input())):
		l += (list(map(int, input().split())),)
	return l

def fecho_convexo(pontos):
	borda = pontos[:]
	for i in pontos:
		for j in pontos:
			if j == i:
				continue
			for k in pontos:
				if k == i or k == j:
					continue
				for l in pontos:
					if l == i or l == k or l == j:
						continue
					if lefton(i, j, l) and lefton(j, k, l) and lefton(k, i, l):
						#print(l, "não é extremo")
						borda = tuple(filter(lambda x: x != l, borda))
	print(borda)

if __name__ == '__main__':
	fecho_convexo(ler())
