#ifndef FACTORIAL_MPFR_H
#define FACTORIAL_MPFR_H

#include <mpfr.h>

unsigned int getPrecision(int p);
void initialize();
void resize_m(int resize);
mpfr_t *factorial_m(mpfr_t *factorial, int num);
void clean_up_m();
void free_mpfr_m(mpfr_t *n);

#endif