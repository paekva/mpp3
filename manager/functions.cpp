#include "functions.h"
#include "message.pb.h"
#include <cstdint>
#include <cstdio>
#include <unistd.h>

void *fibbonachiThread(void * args){
    printf("Inside fibbonachiThread\n");
    TMessage *message = (TMessage *)args;
}

void *powThread(void * args){
    printf("Inside powThread\n");
    TMessage *message = (TMessage *)args;

}

void *bubbleSortThread(void * args){
    printf("Inside bubbleSortThread\n");
    TMessage *message = (TMessage *)args;
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