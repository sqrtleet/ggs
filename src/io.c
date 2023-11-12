#include "io.h"

#include <stdio.h>
#include <stdlib.h>

int input(char **arr) {
    int n = 0;
    char c;
    *arr = (char *)malloc(2 * sizeof(char));
    while ((c = getchar()) != '\n') {
        if (n > 0) {
            *arr = (char *)realloc(*arr, (n + 2));
        }
        (*arr)[n] = c;
        n++;
    }
    (*arr)[n] = '\0';
    return 0;
}

void output(char *arr) {
    for (char *i = arr; *i != '\0'; i++) {
        printf("%c", *i);
    }
}