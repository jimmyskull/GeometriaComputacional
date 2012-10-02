#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "input.h"
#include "../benchmark.h"
#include "../mean.h"

#define RUNS 1

struct benchmark *bm;
struct input *input;
Point *input_array; /* Sorted input. */
long isize;

static void init_input_array(void)
{
    input_array = malloc(isize * sizeof(Point));
    if (input_array == NULL) {
        fprintf(stderr, "Não há espaço na memória para a entrada.\n");
        exit(EXIT_FAILURE);
    }
    input_to_sorted_array(input, input_array);
}

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
    init_input_array();
    bm_init(&bm);

    do_run("Força bruta n⁴", brute_force);
    do_run("Força bruta n³", brute_force_by_edges);
    do_run("Gift wrapping ", gift_wrapping);

    bm_free(&bm);
    input_free(input);
    free(input_array);
    return EXIT_SUCCESS;
}

