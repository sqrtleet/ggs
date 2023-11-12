#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "rpn.h"

#define N_SIZE 25
#define M_SIZE 80

int main() {
    char *arr = NULL, *rpn = NULL;
    // char operators[4] = {'+', '-', '*', '/'};
    input(&arr);
    get_rpn(arr, &rpn);
    output(rpn);
    free(arr);
    free(rpn);
    return 0;
}