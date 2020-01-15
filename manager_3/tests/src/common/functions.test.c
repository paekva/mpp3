#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "../../../common/functions.h"

void fibbonacciTest(uint8_t arg, uint8_t expected){
    uint8_t actual = fibbonacci(arg);
    printf("%d \n", actual);
    assert(expected == actual);
}

void powTest(uint8_t base, int8_t power, uint8_t expected){
    uint8_t actual = powMethod(base, power);
    assert(expected == actual);
}