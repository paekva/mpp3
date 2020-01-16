#include <unistd.h>
#include <stdlib.h>
#include "types.h"
#include "../io/fileWriter.h"

pthread_mutex_t statisticsMutex = PTHREAD_MUTEX_INITIALIZER;

uint8_t fibbonacci(uint8_t number){
    if(number < 1) return 0;
    if(number == 1) return 1;

    return fibbonacci(number-1) + fibbonacci(number-2);
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
    struct timespec startTime, endTime;
    long int duration;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    uint8_t *result = (uint8_t *)malloc(sizeof(uint8_t *));

    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t num = args->tMessage->Data[0];

    clock_gettime(CLOCK_REALTIME, &startTime);
    *result = fibbonacci(num);
    clock_gettime(CLOCK_REALTIME, &endTime);

    duration = convertToMicroSeconds(endTime) - convertToMicroSeconds(startTime);
    writeToFileSingle(args->statistics, &statisticsMutex, (long)duration);

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    return result;
}

void *powTask(void * _args){
    struct timespec startTime, endTime;
    long int duration;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    uint8_t *result = (uint8_t *)malloc(sizeof(uint8_t *));

    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t * fibNum = args->tMessage->Data;

    clock_gettime(CLOCK_REALTIME, &startTime);
    *result = powMethod(fibNum[0], fibNum[1]);
    clock_gettime(CLOCK_REALTIME, &endTime);

    duration = convertToMicroSeconds(endTime) - convertToMicroSeconds(startTime);
    writeToFileSingle(args->statistics, &statisticsMutex, (long)duration);

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    return result;
}

void *bubbleSortTask(void * _args){
    struct timespec startTime, endTime;
    long int duration;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    ThreadArgs *args = (ThreadArgs *)_args;

    clock_gettime(CLOCK_REALTIME, &startTime);
    uint8_t *result = bubbleSort(args->tMessage->Data, args->tMessage->Size);
    clock_gettime(CLOCK_REALTIME, &endTime);

    duration = convertToMicroSeconds(endTime) - convertToMicroSeconds(startTime);
    writeToFileSingle(args->statistics, &statisticsMutex, (long)duration);

    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
    return result;
}