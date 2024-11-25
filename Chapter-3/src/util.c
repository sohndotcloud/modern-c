#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int *sliceIntArray(int *source, int from, int to, int *target) {
    if (to <= from) {
        return NULL;
    }

    unsigned long mem_block_size = (to - from) * sizeof(int);

    if (target == NULL) {
        target = malloc(mem_block_size);
        if (target == NULL) {
            return NULL;
        }
    }

    memcpy(target, &(source[from]), mem_block_size);

    return target;
}