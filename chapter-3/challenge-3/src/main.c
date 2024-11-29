#include <stdio.h>
#include <stdlib.h>
#include "factorial.h"


int main(int argc, char * argv[argc+1]) {
    initialize();
    factorial(10);
    cleanUp();

    return 0;
}