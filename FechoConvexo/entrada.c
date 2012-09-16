#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "entrada.h"

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

