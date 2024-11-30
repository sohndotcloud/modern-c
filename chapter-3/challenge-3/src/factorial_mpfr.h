
#include <mpfr.h>

void initialize_m();
void* allocate_m();
void resize_m(int resize);
mpfr_t* factorial_m(int num);
void clean_up_m();