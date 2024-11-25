#include <stdio.h>

double numerical_derivative(double (*F)(double), double x, double h) {
    return (F(x + h) - F(x - h)) / (2 * h);
}

// Taylor Series Sine
// ∑    =  (−1)n  *   x2n+1
// n=0               (2n + 1)! 
// 
// 
double sine(double x) {
    double result = 0;
    double term = x;  
    int sign = 1;  
    for (int i = 1; i <= 9; i += 2) {  
        result += sign * term;
        sign = -sign;
        term *= x * x / ((i + 1) * (i + 2));  
    }
    return result;
}

double cosine(double x) {
    double result = 0;
    double term = 1;  
    int sign = 1;  
    for (int i = 0; i <= 8; i += 2) {  
        result += sign * term;
        sign = -sign;
        term *= x * x / ((i + 1) * (i + 2));  
    }
    return result;
}

double F(double x) {
    return sine(x);
}

int main(int argc, char * argv[argc+1]) {
    double x = 3.14159265358979 / 4;  // pi/4, which is 45 degrees
    
    // Compute the numerical derivative of sine at x = pi/4
    double num_derivative = numerical_derivative(sine, x, 1e-5);
    
    // Compute the exact derivative of sine at x = pi/4 (which is cosine)
    double exact_derivative = cosine(x);
    
    // Output the results
    printf("Numerical derivative at x = %f is %g\n", x, num_derivative);
    printf("Exact derivative at x = %f is %g\n", x, exact_derivative);
    
    return 0;
}