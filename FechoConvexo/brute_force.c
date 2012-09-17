#include <stdbool.h>
#include <stdlib.h>
#include "algorithm.h"
#include "geometry.h"

#define CMP(a,b) pointcmp(a->value, b->value)
#define LEFTON(a,b,c) lefton(a->value, b->value, c->value)

void brute_force(struct input *input, int size)
{
    Point discarded[size];
    long c, dcount = 0;
    struct input *i, *j, *k, *l;

    for (i = input; i; i = i->next) {
        for (j = input; j; j = j->next) {
            if (CMP(j, i))
                continue;
            for (k = input; k; k = k->next) {
                if (CMP(k, i) || CMP(k, j))
                    continue;
                for (l = input; l; l = l->next) {
                    if (CMP(l, i) || CMP(l, j) || CMP(l, k))
                        continue;
                    if (LEFTON(i,j,l) && LEFTON(j,k,l) && LEFTON(k,i,l)) {
                        bool found = false;

                        for (c = 0; !found && c < dcount; c++)
                            found = pointcmp(discarded[c], l->value);
                        if (!found) {
                            discarded[dcount].X = l->value.X;
                            discarded[dcount].Y = l->value.Y;
                            dcount++;
                        }
                    }
                } /* l */
            } /* k */
        } /* j */
    } /* i */

    long chull = 0;
    Point hull[size - dcount];
    while (input != NULL) {
        bool found = false;

        for (c = 0; !found && c < dcount; c++)
            found = pointcmp(discarded[c], input->value);
        if (!found) {
            hull[chull].X = input->value.X;
            hull[chull++].Y = input->value.Y;
        }
        input = input->next;
    }

#ifndef NDEBUG
    long id;
    for (id = 0; id < chull; id++)
        printf("%d %d\n", hull[id].X, hull[id].Y);
#endif
}

