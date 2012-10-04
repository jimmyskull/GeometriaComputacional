#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#ifndef NDEBUG
#  include <stdio.h>
#  define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#  define debug(...)
#endif

struct input;

/* Alguns algoritmos recebem uma lista encadeada de pontos
 * e quantidade de pontos na lista. */
typedef void (*alg_fn_t)(const struct input *, const int);

/* brute_force.c */
extern void brute_force(const struct input *, const int);

extern void brute_force_by_edges(const struct input *, const int);

/* gift_wrapping.c */
extern void gift_wrapping(const struct input *, const int);

/* insertion_hull.c */
extern void insertion_hull(const struct input *, const int);

#endif /* __ALGORITHM_H__ */

