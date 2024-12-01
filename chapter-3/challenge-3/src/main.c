#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include "factorial_mpfr.h"
#include "mpfr_wrapper.h"
#include "main.h"

int LOG2_10 = 4;

int main(int argc, char * argv[argc+1]) {
    chudnovsky(5);
}

void chudnovsky(unsigned long k) {
    mpfr_t sum;
    mpfr_t* result;
    result = malloc(sizeof(mpfr_t));
    int precision = calcPrecision(k) * LOG2_10;
    setPrecision(precision);
    mpfr_t* constant = calcConstant();
    mpfr_t pi_inverse;
    init(pi_inverse);
    set_ui(pi_inverse, 0);
    
    // CALCULATIONS
    for (int i = 0; i <= k; i++) {
        mpfr_t* numValue = numerator(k);
        mpfr_t* denomValueA = denominator_a(k);
        mpfr_t* denomValueB = denominator_b(k);
        init(*result);
        mul(*denomValueA, *denomValueA, *denomValueB);
        m_div(*result, *numValue, *denomValueA);

        free_mpfr_m(numValue);
        free_mpfr_m(denomValueA);
        free_mpfr_m(denomValueB);
        char result_str[500];  
        mpfr_sprintf(result_str, "%Rf", *result);
        printf("String representation of x: %s\n", result_str);
        add(pi_inverse, pi_inverse, *result);
        clear(*result);
    }
    
    mpfr_t pi, one;
    init(one);
    init(pi);
    set_ui(one, 1);
    mul(pi_inverse, pi_inverse, *constant);
    m_div(pi, one, pi_inverse);
    
    clear(sum);

    free_mpfr_m(result);
    free_mpfr_m(constant);
    clean_up_m();
}

int calcPrecision(int numTerms) {
    const int PLACES_PER_TERM = 14;
    return numTerms * PLACES_PER_TERM;
}

// constant = 1 / (426880 * sqrt(10005)) 
mpfr_t* calcConstant(){
    mpfr_t numerator;
    mpfr_t denominator_a;// = 426880;
    mpfr_t denominator_b_squared;// = 10005;
    mpfr_t denominator;
    mpfr_t* result = malloc(sizeof(mpfr_t));
    init(numerator);
    init(denominator_a);
    init(denominator_b_squared);
    init(denominator);
    init(*result);
    
    set_ui(numerator, 1);
    set_ui(denominator_a, 426880);
    set_ui(denominator_b_squared,10005);

    mpfr_sqrt(denominator_b_squared, denominator_b_squared, MPFR_RNDN);
    mul(denominator, denominator_a, denominator_b_squared);
    m_div(*result, numerator, denominator);

    clear(numerator);
    clear(denominator);
    clear(denominator_a);
    clear(denominator_b_squared);
    return result;
}

// (-1)^k * 6k! * 545140134 * k + 1359104
mpfr_t* numerator(int k) {
    mpfr_t* six_k_fact = malloc(sizeof(mpfr_t));
    init(*six_k_fact);

    six_k_fact = factorial_m(six_k_fact, 6 * k);
    mpfr_t k_constant, constant;
    init(constant);
    init(k_constant);
    set_ui(k_constant, 545140134);
    set_ui(constant, 1359104);
    mul_ui(k_constant, k_constant, k);
    add(k_constant, k_constant, constant);

    int sign = (k & 1 ? -1 : 1);
    mpfr_t* result;
    result = malloc(sizeof(mpfr_t));
    init(*result);
    set_si(*result, sign);
    mul(*result, *result, *six_k_fact);
    mul(*result, *result, k_constant);

    clear(k_constant);
    clear(constant);
    free_mpfr_m(six_k_fact);
    return result; 
}

// 3k! * (k!) ^ 3
mpfr_t* denominator_a(int k) {
    mpfr_t* factorial_k = malloc(sizeof(mpfr_t));
    factorial_k = factorial_m(factorial_k, k);
    mpfr_t* factorial_3k = malloc(sizeof(mpfr_t));
    factorial_3k = factorial_m(factorial_3k, 3 * k);
    mpfr_t* result = malloc(sizeof(mpfr_t));
    mpfr_t factorial_k_cubed;
    init(factorial_k_cubed);
    init(*result);
    pow_si(factorial_k_cubed, factorial_3k, 3);
    mul(*result, factorial_3k, factorial_k_cubed);

    free_mpfr_m(factorial_3k);
    free_mpfr_m(factorial_k);
    clear(factorial_k_cubed);
    return *result;
}

// 640320 ^ 3k
mpfr_t* denominator_b (int k) {
    mpfr_t* result;
    init(*result);
    set_ui(*result, 640320);
    pow_si(*result, *result, k * 3);
    return result;
}
