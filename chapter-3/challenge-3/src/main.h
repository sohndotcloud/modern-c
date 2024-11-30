#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include "factorial_mpfr.h"
#include "mpfr_wrapper.h"


void chudnovsky(unsigned long num_terms);