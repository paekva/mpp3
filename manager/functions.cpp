#include "functions.h"
#include "message.pb.h"
#include "types.h"
#include <cstdint>
#include <cstdio>
#include <unistd.h>

void *fibbonachiThread(void * _args){
    printf("Inside fibbonachiThread\n");
    ThreadArgs *args = (ThreadArgs *)_args;
    args->resultArgs->results->push_front("done");
}

void *powThread(void * _args){
    printf("Inside powThread\n");
    ThreadArgs *args = (ThreadArgs *)_args;
    args->resultArgs->results->push_front("done");
}

void *bubbleSortThread(void * _args){
    printf("Inside bubbleSortThread\n");
    ThreadArgs *args = (ThreadArgs *)_args;
    args->resultArgs->results->push_front("done");
}

int fibbonachi(int number){
    if(number>1){
        return fibbonachi(number-1) + fibbonachi(number-2);
    } else return number;
}

uint64_t* bubbleSort(uint64_t* array, int arrayLength){
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

int pow(int base, int power){
    int i;
    long result = 1;
    for(i = 0; i<power; i++){
        result = result * base;
    }
    return result;
}