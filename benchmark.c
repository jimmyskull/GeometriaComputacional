#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "benchmark.h"

struct benchmark {
    double begin;
    double end;
};

static double get_time()
{
    struct timeval t;
    void *tzp;

    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec * 1e-6;
}

void bm_init(struct benchmark **self)
{
    *self = calloc(1, sizeof(struct benchmark));
    assert(*self != NULL);
}

void bm_free(struct benchmark **self)
{
    if (*self != NULL)
        free(*self);
    *self = NULL;
}

void bm_start(struct benchmark *self)
{
    assert(self != NULL);
    self->begin = get_time();
}

void bm_finish(struct benchmark *self)
{
    assert(self != NULL);
    self->end = get_time();
}

double bm_result(const struct benchmark *self)
{
    assert(self != NULL);
    return self->end - self->begin;
}
