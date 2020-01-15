#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "../../../common/functions.h"

void fibbonacciTest(uint8_t arg, uint8_t expected){
    uint8_t actual = fibbonacci(arg);
    assert(expected == actual);
}

void powTest(uint8_t base, int8_t power, uint8_t expected){
    uint8_t actual = powMethod(base, power);
    assert(expected == actual);
}

void bubbleSortTest(uint8_t size, uint8_t *array, uint8_t* expected){
    uint8_t* actual = bubbleSort(array, size);

    for(int i=0; i< size; i++){
        assert(expected[i] == actual[i]);
    }
}