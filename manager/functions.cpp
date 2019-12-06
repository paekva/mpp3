#include "message.pb.h"
#include "types.h"
#include <cstdint>
#include <cstdio>
#include <pthread.h>

void addResult(ResultArgs *resultArgs, std::string message){
    pthread_mutex_lock(resultArgs->resultsMutex);
    resultArgs->results->push_front(message);
    pthread_mutex_unlock(resultArgs->resultsMutex);
}

void *fibbonachiThread(void * _args){
    printf("Inside fibbonachiThread\n");
    auto *args = (ThreadArgs *)_args;
    addResult(args->resultArgs, "fibb done");
}

void *powThread(void * _args){
    printf("Inside powThread\n");
    auto *args = (ThreadArgs *)_args;
    addResult(args->resultArgs, "pow done");
}

void *bubbleSortThread(void * _args){
    printf("Inside bubbleSortThread\n");
    auto *args = (ThreadArgs *)_args;
    addResult(args->resultArgs, "sort done");
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