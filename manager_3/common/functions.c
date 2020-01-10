#include "types.h"
#include "queue.h"

int fibbonachi(int number){
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

int powMethod(int base, int power){
    int i;
    int result = 1;
    for(i = 0; i<power; i++){
        result = result * base;
    }
    return result;
}

void *fibbonachiThread(void * _args){
    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t num = args->tMessage->Data[0];
    int result = fibbonachi(num);
    // printf("result %d %d\n", num, result);
    addToQueue(args->results, &result);
}

void *powThread(void * _args){
    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t * fibNum = args->tMessage->Data;
    int result = powMethod(fibNum[0], fibNum[1]);
    addToQueue(args->results, &result);
}

void *bubbleSortThread(void * _args){
    ThreadArgs *args = (ThreadArgs *)_args;
    uint8_t *result = bubbleSort(args->tMessage->Data, args->tMessage->Size);
    addToQueue(args->results, result);
}