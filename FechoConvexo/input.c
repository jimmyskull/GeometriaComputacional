#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

struct input *input_read(void)
{
    struct input *node, *last = NULL, *lst = NULL;
    int n, r;

    if (scanf("%d", &n) != 1)
        return NULL;
    while (n--) {
        node = malloc(sizeof(struct input));
        assert(node != NULL);
        r = scanf("%d %d", &node->value.X, &node->value.Y);
        assert(r == 2);
        if (last == NULL)
            lst = last = node;
        else
            last = (last->next = node);
    }
    if (last != NULL)
        last->next = NULL;
    return lst;
}

/* Ordernar pela coordenada Y */
static int qsort_point_cmp(const Point *a, const Point *b)
{
    int ret = b->Y - a->Y;

    if (ret == 0)
        ret = b->X - a->X;
    return ret;
}

void input_to_sorted_array(const struct input *input, Point *sorted)
{
    Point *arr = sorted;
    size_t count = 0;

    while (input != NULL && ++count) {
        *arr++ = input->value;
        input = input->next;
    }
    qsort(sorted, count, sizeof(Point), (__compar_fn_t) qsort_point_cmp);
}

void input_free(struct input *input)
{
    struct input *node;

    while ((node = input) != NULL) {
        input = input->next;
        free(node);
    }
}

long input_size(struct input *input)
{
    long count = 0;
    while (input != NULL && ++count)
        input = input->next;
    return count;
}

