#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#ifndef NDEBUG
#  include <stdio.h>
#  define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#  define debug(...)
#endif

struct input;

/* Todos os algoritmos são chamados passando uma lista
 * encadeada dos elementos da entrada e o inteiro com
 * a quantidade de elementos na lista. */

/* brute_force.c */
extern void brute_force(const struct input *, const int);

extern void brute_force_by_edges(const struct input *, const int);

extern void gift_wrapping(const struct input *, const int);

#endif /* __ALGORITHM_H__ */

