#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <pthread.h> 
#include <stdio.h>
#include "mpfr_wrapper.h"

typedef struct  {
    mpfr_t ** list;
    int size;
} factorial_mpfr_t;

factorial_mpfr_t *m;


void initialize_m() {
    printf("Initializing...\n");
    int size = 2;
    m = malloc(sizeof(factorial_mpfr_t));
    m->list = calloc(size, sizeof(mpfr_t*));
    printf("List created...\n");
    for (int i = 0; i < size; i++) {
        printf("Loading mpfr...%d\n", i);
        m->list[i] = malloc(sizeof(mpfr_t));
        init(*m->list[i]);
        set_ui(*m->list[i], 1);
    }
    m->size = size;
}

void resize_m(int resize) {
    if (m->size >= resize) {
        return;
    }

    unsigned long mpfr_block = sizeof(mpfr_t);
    int new_block_size = resize * mpfr_block;
    printf("Block size changing from %lu >>>>> %d\n", m->size * mpfr_block, new_block_size);
    printf("Size changing %d >>>>> %d\n", m->size, resize);
    
    m->list = realloc(m->list, new_block_size);
    if (m->list == NULL) {
        fprintf(stderr, "Reallocation failed\n");
        return;
    }

    for(int i = m->size; i <= resize; i++) {
        m->list[i] = malloc(mpfr_block);
        init(*m->list[i]);
        set_ui(*m->list[i], 1);
    }
    m->size = resize;
}

mpfr_t* factorial_m(int num) {
    if (num < 0 && num > INT_MAX) {
        return NULL;
    }

    if (m == NULL) {
        initialize_m();
    }
    
    mpfr_t* factorial = malloc(1 * sizeof(mpfr_t));
    init(*factorial);
    set(*factorial, *m->list[0]);
    num++;

    if (m->size > num) {
        return m->list[num];
    } else {
        int index = m->size - 1;
        set(*factorial, *m->list[index]);
        resize_m(num);
        for (int i = index; i <= num; i++) {
            mul_ui(*factorial, *factorial, i);
            set(*m->list[i], *factorial);
        }
    }

    return factorial;
}

void clean_up_m() {
    if (m == NULL || m->list == NULL) return;

    for (int i = 0; m->size > i; i++) {
        if (m->list[i] != NULL) {
            clear(*m->list[i]);
            free(m->list[i]);
        }
    }

    free(m->list);
    m->size = 0;
}