#include "common/functions.test.h"
#include <stdio.h>

int main(int arg, char* argv[]){
    printf("fibbonacci test 1\n");
    fibbonacciTest(7, 13);

    printf("fibbonacci test 2\n");
    fibbonacciTest(2, 1);

    printf("fibbonacci test 3\n");
    fibbonacciTest(0, 0);


    printf("power test 1\n");
    powTest(2,7, 128);

    printf("power test 2\n");
    powTest(2,0, 1);


    printf("bubble sort test 1\n");
    uint8_t array[5] = {3, 2, 5, 1, 0};
    uint8_t expected[5] = {0, 1, 2, 3, 5};
    bubbleSortTest(5, &array[0], &expected[0]);
    return 0;
}
