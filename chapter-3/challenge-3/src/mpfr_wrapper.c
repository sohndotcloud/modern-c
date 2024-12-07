#include <mpfr.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpfr_wrapper.h"

// mpfr_wrapper.c

int defaultPrecision = 514;

void init2(mpfr_t n, int size)
{
    mpfr_init2(n, size);
}

void init(mpfr_t n)
{
    mpfr_init2(n, defaultPrecision);
}

mpfr_t *initPtr()
{
    mpfr_t *ptr = malloc(sizeof(mpfr_t));
    init(*ptr);
    return ptr;
}

void setDefaultPrecision(int precision)
{
    defaultPrecision = precision;
}

int getDefaultPrecision()
{
    return defaultPrecision;
}

unsigned int getPrecision(int p)
{
    unsigned int bits = 14 * p * log2(10);
    return bits < 1024 ? 1024 : bits;
}

void set(mpfr_t n, mpfr_t m)
{
    mpfr_set(n, m, R);
}

void set_ui(mpfr_t n, unsigned long x)
{
    mpfr_set_ui(n, x, R);
}

void set_si(mpfr_t n, long x)
{
    mpfr_set_si(n, x, R);
}

long get_ui(mpfr_t n)
{
    return mpfr_get_ui(n, R);
}

void mul(mpfr_t n, mpfr_t m, mpfr_t p)
{
    mpfr_mul(n, m, p, R);
}

void mul_si(mpfr_t n, mpfr_t m, long x)
{
    mpfr_mul_si(n, m, x, R);
}

void mul_ui(mpfr_t n, mpfr_t m, unsigned long x)
{
    mpfr_mul_ui(n, m, x, R);
}

void pow_si(mpfr_t n, mpfr_t m, long x)
{
    mpfr_pow_si(n, m, x, R);
}

void add_ui(mpfr_t n, unsigned long x)
{
    mpfr_add_ui(n, n, x, R);
}

void add(mpfr_t n, mpfr_t m, mpfr_t p)
{
    mpfr_add(n, m, p, R);
}

void m_div(mpfr_t n, mpfr_t m, mpfr_t p)
{
    mpfr_div(n, m, p, R);
}

void clear(mpfr_t x)
{
    mpfr_clear(x);
}

void print(char *message, mpfr_t value)
{
    char msg[1024];
    mpfr_sprintf(msg, "%-s %-.10Re", message, value);
    printf("%s\n", msg);
}