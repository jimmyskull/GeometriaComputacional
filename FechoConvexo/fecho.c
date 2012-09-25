#include <stdio.h>
#include "algorithm.h"
#include "input.h"
#include "../benchmark.h"
#include "../mean.h"

#define RUNS 1

struct benchmark *bm;
struct input *input;
long isize;

static void do_run(const char *name, 
    void (*algorithm)(const struct input *, const int))
{
    int i;
    double exec[RUNS];

    for (i = 0; i < RUNS; i++) {
        printf("\n");
        bm_start(bm);
        algorithm(input, isize);
        bm_finish(bm);
        exec[i] = bm_result(bm);
        printf("\r%s (%d/%d): %lf seconds", name, i + 1, RUNS, exec[i]);
        fflush(stdout);
    }
    if (RUNS > 1)
        printf(" => Média: %lf ~ %lf\n", mean(exec, RUNS), 
                standard_deviation(exec, RUNS));
    else
        printf("\n");
}

int main()
{
    input = input_read();
    isize = input_size(input);
    bm_init(&bm);

    do_run("Força bruta n⁴", brute_force);
    do_run("Força bruta n³", brute_force_by_edges);

    bm_free(&bm);
    input_free(input);
    return 0;
}

