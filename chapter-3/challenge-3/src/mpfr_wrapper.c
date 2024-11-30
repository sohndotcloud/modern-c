#include <mpfr.h>
#include "mpfr_wrapper.h"

void init(mpfr_t n) {
    mpfr_init2(n, BLOCK_SIZE);
}

void set(mpfr_t n, mpfr_t m) {
    mpfr_set(n, m, R);
}

void set_ui(mpfr_t n, unsigned long x) {
    mpfr_set_ui(n, x, R);
}

long get_ui(mpfr_t n) {
    return mpfr_get_ui(n, R);
}

void mul(mpfr_t n, mpfr_t m, mpfr_t p) {
    mpfr_mul(n, m, p, R);
}

void mul_ui(mpfr_t n, mpfr_t m, unsigned long x) {
    mpfr_mul_ui(n, m, x, R);
}

void add_ui(mpfr_t n, unsigned long x) {
    mpfr_add_ui(n, n, x, R);
}

void clear(mpfr_t x) {
    mpfr_clear(x);
}