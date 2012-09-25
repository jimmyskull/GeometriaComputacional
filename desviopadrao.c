#include <math.h>
#include "desviopadrao.h"
#include <stdio.h>

double mean(double *vector, const int size)
{
    double total = 0.0;
    int n = size;

    while (n--)
        total += *vector++;
    return total / size;
}

double standard_deviation(double *vector, const int size)
{
    double m = mean(vector, size);
    double sum = 0.0;
    int n = size;

    while (n--)
        sum += pow(*vector++ - m, 2.0);
    return sqrt( ((double) 1.0 / (size - 1.0)) * sum );
}

