#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <pthread.h> 
#include <stdio.h>
#include "factorial.h"

typedef struct  {
    int ** list;
    int size;

} factorial_t;

factorial_t *f;


void initialize() {
    printf("Initializing...\n");
    int size = 2;
    f = malloc(1 * sizeof(factorial_t));
    f->list = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        f->list[i] = malloc(1 * sizeof(int));
        *f->list[i] = 1;
    }
    f->size = size;
}

void resize(int resize) {
    for (int i = 0; i < f->size - 1; i++) {
        printf("%d %d\n", i, *f->list[i]);
    }
    printf("\n");

    int block_size = resize * sizeof(int*);
    printf("Resizing block from %lu to %d\n", f->size * (sizeof(int*)), block_size);
    printf("Size is %d %d\n", f->size, resize);
    
    f->list = realloc(f->list, block_size);

    for(int i = f->size; i <= resize; i++) {
        f->list[i] = malloc(1 * sizeof(int));
        *f->list[i] = 1;
    }
    f->size = resize;
}

int factorial(int num) {
    if (num < 0 && num >= INT_MAX) {
        return 1;
    }

    int factorial = *f->list[f->size - 1];
    num++;

    if (f->size > num) {
        printf("Hello!");
        return *f->list[num];
    } else {
        printf("F is %d\n", factorial);
        int index = f->size - 1;
        factorial = *f->list[index];
        resize(num);
        for (int i = index; i <= num; i++) {
            factorial *= i;
            *f->list[i] = factorial;
        }
    }

    return factorial;
}

void cleanUp() {
    for (int i = f->size; i > 0; --i) {
        free(f->list[i]);
    }
    free(f->list);
}