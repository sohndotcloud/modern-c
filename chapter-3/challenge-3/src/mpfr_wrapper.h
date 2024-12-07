#ifndef MPFR_WRAPPER_H
#define MPFR_WRAPPER_H
#define R MPFR_RNDN

#include <mpfr.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void set(mpfr_t n, mpfr_t m);
void init(mpfr_t n);
void init2(mpfr_t n, int size);

void set(mpfr_t n, mpfr_t m);
void set_ui(mpfr_t n, unsigned long x);
void set_si(mpfr_t n, long x);

long get_ui(mpfr_t n);

void mul(mpfr_t n, mpfr_t m, mpfr_t p);
void mul_ui(mpfr_t n, mpfr_t m, unsigned long x);

void clear(mpfr_t x);

void add_ui(mpfr_t n, unsigned long x);
void add(mpfr_t n, mpfr_t m, mpfr_t p);

void setDefaultPrecision(int precision);
int getDefaultPrecision();
unsigned int getPrecision(int p);

void pow_si(mpfr_t n, mpfr_t m, long x);

void m_div(mpfr_t n, mpfr_t m, mpfr_t p);

void print(char *message, mpfr_t value);

mpfr_t *initPtr();

#endif