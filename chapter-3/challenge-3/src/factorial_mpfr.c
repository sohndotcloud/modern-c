#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include <pthread.h> 
#include <stdio.h>
#include <math.h>
#include "mpfr_wrapper.h"
#include "factorial_mpfr.h"

// factorial_mpfr.c

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
    for (int i = 0; i < size; i++) {
        m->list[i] = malloc(sizeof(mpfr_t));
        init2(*m->list[i], 2);
        set_ui(*m->list[i], 1);
    }
    m->size = size;
}

unsigned int get_precision(int p) {
    double precision = (p * log2(p) - 1.4427 * p);
    unsigned int bits = (unsigned int) precision + 1;
    if (bits > 100) {
        bits = 100;
    }
    return bits < 53 ? 53 : bits;
}

void resize_m(int resize) {
    if (m->size >= resize) {
        return;
    }

    unsigned long mpfr_block = sizeof(mpfr_t);
    int new_block_size = resize * mpfr_block;
    printf("Block size changing from %lu >>>>> %d\n", m->size * mpfr_block * m->size, new_block_size);
    printf("Size changing %d >>>>> %d\n", m->size, resize);
    
    m->list = realloc(m->list, new_block_size);
    if (m->list == NULL) {
        fprintf(stderr, "Reallocation failed\n");
        return;
    }

    for(int i = m->size; i <= resize; i++) {
        int bits = get_precision(i);
        m->list[i] = malloc(mpfr_block);
        if (m->list == NULL) {
            fprintf(stderr, "Reallocation failed\n");
            return;
        }

        init2(*m->list[i], bits);
        set_ui(*m->list[i], 1);
    }
    m->size = resize;
}

mpfr_t* factorial_m(mpfr_t* factorial, int base) {
    if (base < 0 && base >= 300) {
        return NULL;
    }

    if (m == NULL) {
        initialize_m();
    }
    
    init2(*factorial, get_precision(base));
    set(*factorial, *m->list[0]);
    base++;

    if (m->size > base) {
        return m->list[base];
    } else {
        int index = m->size - 1;
        set(*factorial, *m->list[index]);
        resize_m(base);
        for (int i = index; i <= base; i++) {
            mul_ui(*factorial, *factorial, i);
            set(*m->list[i], *factorial);
        }
    }

    return factorial;
}

void clean_up_m() {
    if (m == NULL || m->list == NULL) return;

    for (int i = 0; i <= m->size; i++) {
        free_mpfr_m(m->list[i]);
        m->list[i] = NULL;
    }

    free(m->list);
    m->list = NULL;
    m->size = 0;
    free(m);
}

void free_mpfr_m(mpfr_t* n) {
    if (n != NULL) {
        clear(*n);
        free(n);
    }
}