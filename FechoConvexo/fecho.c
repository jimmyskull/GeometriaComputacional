#include <stdio.h>
#include "entrada.h"

int main()
{
    struct input *input;

    input = input_read();

    input_free(input);
    input = NULL;


    return 0;
}


