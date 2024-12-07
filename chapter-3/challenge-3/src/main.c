#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include <math.h>
#include "factorial_mpfr.h"
#include "mpfr_wrapper.h"
#include "main.h"

const int LOG2_10 = 4;

int main(int argc, char *argv[argc + 1])
{
    // Limit = 49
    // Factorial function loses precision around 300!
    chudnovsky(49);
}

void chudnovsky(unsigned long k)
{
    int precision = getPrecision(k) * LOG2_10;
    setDefaultPrecision(precision);
    mpfr_t *constant = calcConstant();
    mpfr_t pi_inverse;
    init(pi_inverse);
    set_ui(pi_inverse, 0);
    mpfr_t *result = NULL;

    // CALCULATIONS
    for (int i = 0; i <= k; i++)
    {
        if (result != NULL)
        {
            free_mpfr_m(result);
        }
        result = initPtr();
        mpfr_t *numValue = numerator(i);
        mpfr_t *denomValueA = denominator_a(i);
        mpfr_t *denomValueB = denominator_b(i);
        mul(*denomValueA, *denomValueA, *denomValueB);
        m_div(*result, *numValue, *denomValueA);
        add(pi_inverse, pi_inverse, *result);
        free_mpfr_m(numValue);
        free_mpfr_m(denomValueA);
        free_mpfr_m(denomValueB);
        print("Series value:", *result);
    }

    mpfr_t pi, twelve;
    mpfr_init2(twelve, precision);
    init(pi);
    set_si(twelve, 12);
    print("pi_inverse", pi_inverse);
    mul(pi_inverse, pi_inverse, twelve);
    print("pi_inverse * 12", pi_inverse);
    mpfr_ui_div(pi, 1, pi_inverse, MPFR_RNDN);
    print("pi_inverse * 12 * constant = pi ", pi);
    free_mpfr_m(result);
    free_mpfr_m(constant);
    clean_up_m();
}

// constant = 1 / (426880 * sqrt(10005))
mpfr_t *calcConstant()
{
    mpfr_t numerator;
    mpfr_t denominator_a;         // = 426880;
    mpfr_t denominator_b_squared; // = 10005;
    mpfr_t denominator;
    mpfr_t *result = initPtr();
    init(numerator);
    init(denominator_a);
    init(denominator_b_squared);
    init(denominator);
    set_ui(numerator, 1);
    set_ui(denominator_a, 426880);
    set_ui(denominator_b_squared, 10005);
    mpfr_sqrt(denominator_b_squared, denominator_b_squared, MPFR_RNDN);
    mul(denominator, denominator_a, denominator_b_squared);
    mpfr_div(*result, numerator, denominator, MPFR_RNDN);
    clear(numerator);
    clear(denominator);
    clear(denominator_a);
    clear(denominator_b_squared);
    return result;
}

// (-1)^k * 6k! * (545140134 * k + 1359104)
mpfr_t *numerator(int k)
{
    mpfr_t *six_k_fact = initPtr();
    six_k_fact = factorial_m(six_k_fact, 6 * k);
    mpfr_t k_constant, constant;
    init(constant);
    init(k_constant);
    set_ui(constant, 13591409);
    set_ui(k_constant, 545140134);
    mul_ui(k_constant, k_constant, k);
    add(k_constant, k_constant, constant);
    int sign = (k & 1 ? -1 : 1);
    setDefaultPrecision(getPrecision(k));
    mpfr_t *result = initPtr();
    set_si(*result, sign);
    mul(*result, *result, *six_k_fact);
    mul(*result, *result, k_constant);
    clear(k_constant);
    clear(constant);
    free_mpfr_m(six_k_fact);
    return result;
}

// 3k! * (k!) ^ 3
mpfr_t *denominator_a(int k)
{
    mpfr_t *factorial_k = initPtr();
    mpfr_t *result = initPtr();
    mpfr_t *factorial_k_cubed = initPtr();
    mpfr_t *factorial_3k = initPtr();
    factorial_k = factorial_m(factorial_k, k);
    factorial_3k = factorial_m(factorial_3k, 3 * k);
    mpfr_pow_ui(*factorial_k_cubed, *factorial_k, 3, MPFR_RNDN);
    mul(*result, *factorial_3k, *factorial_k_cubed);
    free_mpfr_m(factorial_3k);
    free_mpfr_m(factorial_k);
    free_mpfr_m(factorial_k_cubed);

    return result;
}

// 640320 ^ (3k + 3/2)
mpfr_t *denominator_b(int k)
{
    mpfr_t *result = initPtr();
    mpfr_t *integerPart = initPtr();
    mpfr_t *fractionalPart = initPtr();
    int constant = 640320;
    mpfr_init2(*result, getDefaultPrecision());
    set_si(*integerPart, constant);
    set_si(*fractionalPart, constant);
    pow_si(*integerPart, *integerPart, k * 3);
    pow_si(*fractionalPart, *fractionalPart, 3);
    mpfr_sqrt(*fractionalPart, *fractionalPart, MPFR_RNDN);
    mul(*result, *integerPart, *fractionalPart);
    free_mpfr_m(integerPart);
    free_mpfr_m(fractionalPart);
    return result;
}
