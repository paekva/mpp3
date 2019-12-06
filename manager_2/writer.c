#include "queue.h"
#include "stdio.h"

void *writer(void* _args) {
    Queue *resultList = (Queue *)_args;
    int i = 0;
    while(1){
        if(getQueueSize(resultList) != 0){
            char *message = removeFromQueue(resultList);
            printf("\nresult %s\n\n", message);
            i++;
        }

        if(i>2)
            break;
    }
}