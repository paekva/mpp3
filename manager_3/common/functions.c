#include <unistd.h>
#include <stdlib.h>
#include "types.h"

uint8_t fibbonachi(uint8_t number){
    if(number<1) return 0;
    if(number == 1) return 1;
    return fibbonachi(number-1) + fibbonachi(number-2);
}

uint8_t* bubbleSort(uint8_t* array, int arrayLength){
    int i, j;
    for(i = 0; i < arrayLength; i++){
        for(j = arrayLength - 1; j > i; j--){
            if(array[j-1] > array[j]){
                int tmp = array[j-1];
                array[j-1] = array[j];
                array[j] = tmp;
            }
        }
    }
    return array;
}

uint8_t powMethod(uint8_t base, uint8_t power){
    int i;
    uint8_t result = 1;
    for(i = 0; i<power; i++){
        result = result * base;
    }
    return result;
}

void *fibbonachiTask(void * _args){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    uint8_t *result = malloc(sizeof(uint8_t));

    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t num = args->tMessage->Data[0];
    *result = fibbonachi(num);

    sleep(5);

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    return result;
}

void *powTask(void * _args){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    uint8_t *result = malloc(sizeof(uint8_t));

    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t * fibNum = args->tMessage->Data;
    *result = powMethod(fibNum[0], fibNum[1]);

    sleep(5);

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    return result;
}

void *bubbleSortTask(void * _args){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t *result = bubbleSort(args->tMessage->Data, args->tMessage->Size);
    sleep(5);

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    return result;
}