#ifndef __INPUT_H__
#define __INPUT_H__

#include "geometry.h"

struct input {
    Point value;
    struct input *next;
};

/* entrada.c */

/* Lê um número N e mais N linhas de pontos.  Retorna ponteiro
 * para o início da lista de pontos.
 * N
 * X Y
 * X Y
 * ...
 */
extern struct input *input_read(void);

/* Libera a lista de pontos da memória. */
extern void input_free(struct input *);

/* Quantidade de elementos na lista. */
extern long input_size(struct input *);

#endif /* __INPUT_H__ */

