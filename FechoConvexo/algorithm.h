#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#ifndef NDEBUG
#  include <stdio.h>
#  define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#  define debug(...)
#endif

#include "input.h"

/* Todos os algoritmos são chamados passando uma lista
 * encadeada dos elementos da entrada e o inteiro com
 * a quantidade de elementos na lista. */

/* brute_force.c */
extern void brute_force(struct input *, int);

#endif /* __ALGORITHM_H__ */

