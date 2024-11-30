#define R MPFR_RNDN

#include <mpfr.h>

void set(mpfr_t n, mpfr_t m);
void init(mpfr_t n);
void init2(mpfr_t n, int size);
void set(mpfr_t n, mpfr_t m);
void set_ui(mpfr_t n, unsigned long x);
long get_ui(mpfr_t n);
void mul(mpfr_t n, mpfr_t m, mpfr_t p);
void mul_ui(mpfr_t n, mpfr_t m, unsigned long x);
void clear(mpfr_t x);
void add_ui(mpfr_t n, unsigned long x);