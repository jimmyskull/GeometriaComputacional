#include <stdlib.h>
#include "algorithm.h"
#include "geometry.h"
#include "input.h"

void gift_wrapping(const struct input *input, const int size)
{
    const struct input *t, *i = input;
    Point endpt, pt = i->value;
    Point hull[size];
    int chull = 0;

    while (i != NULL) {
        const Point *q = &i->value;

        if (pt.Y > q->Y || (pt.Y == q->Y && pt.X < q->X))
            pt = *q;  
        i = i->next;
    }

    endpt = pointcmp(input->value, pt)? input->next->value: input->value;
    do {
        hull[chull++] = pt;
        for (t = input; t != NULL; t = t->next)
            if (pointcmp(endpt, pt) || !lefton(pt, endpt, t->value))
                endpt = t->value;
        pt = endpt;
    } while (!pointcmp(endpt, hull[0]));

#ifndef NDEBUG
    long id;
    for (id = 0; id < chull; id++)
        printf("%d %d\n", hull[id].X, hull[id].Y);
#endif

}

