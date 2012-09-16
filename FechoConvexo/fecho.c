#include <stdio.h>
#include "algoritmos.h"
#include "entrada.h"
#include "../benchmark.h"

struct benchmark *bm;
struct input *input;
long isize;

static void do_run(const char *name, 
    void (*algorithm)(struct input *, int))
{
    bm_start(bm);
    algorithm(input, isize);
    bm_finish(bm);
    printf("%s: %lf seconds\n", name, bm_result(bm));
}

int main()
{
    input = input_read();
    isize = input_size(input);
    bm_init(&bm);

    do_run("Força bruta", brute_force);

    bm_free(&bm);
    input_free(input);
    return 0;
}


