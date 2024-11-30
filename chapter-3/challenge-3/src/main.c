#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include "factorial_mpfr.h"
#include "mpfr_wrapper.h"
#include "main.h"

int main(int argc, char * argv[argc+1]) {
    // initialize();
    // factorial(10);
    // cleanUp();

    chudnovsky(3);
}

void chudnovsky(unsigned long num_terms) {
    // mpfr_t sum, constant, term, numerator, denominator, factor, power, factorial_k, factorial_3k, factorial_k3;
    // init(sum);
    // init(term);
    // init(numerator);
    // init(denominator);
    // init(constant);
    // init(factor);
    // init(power);
    // init(factorial_k);
    // init(factorial_3k);
    // init(factorial_k3);

    // // Print mpfr
    // char result_str[500];  // Make sure the buffer is large enough
    // set_ui(constant, 350);
    // long c = get_ui(constant);
    // set(sum, *factorial_m(c));
    // mpfr_sprintf(result_str, "%.50Rf", sum);
    // printf("String representation of x: %s\n", result_str);
    initialize_m();
    resize_m(10);

    clean_up_m();
}