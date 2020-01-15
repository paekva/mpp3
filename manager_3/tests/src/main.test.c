#include "common/functions.test.h"
#include <stdio.h>

int main(int arg, char* argv[]){
    printf("fibbonacci test 1\n");
    fibbonacciTest(7, 13);

    printf("power test 1");
    powTest(2,7, 128);
    return 0;
}
