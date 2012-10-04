#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "input.h"
#include "../benchmark.h"
#include "../mean.h"

#define RUNS 5

int i;
double exec[RUNS]; /* Tempo de cada execução. */

struct benchmark *bm;
struct input *input;
long isize;

static void do_run(const char *name, alg_fn_t algorithm)
{
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
        printf(" => Média: %lf ~ %lf", mean(exec, RUNS),
            standard_deviation(exec, RUNS));
    printf("\n");
}

int main(void)
{
    input = input_read();
    isize = input_size(input);
    bm_init(&bm);

    do_run("Insertion hull", insertion_hull);
    do_run("Gift wrapping ", gift_wrapping);
    do_run("Força bruta n³", brute_force_by_edges);
    do_run("Força bruta n⁴", brute_force);

    bm_free(&bm);
    input_free(input);
    return EXIT_SUCCESS;
}

