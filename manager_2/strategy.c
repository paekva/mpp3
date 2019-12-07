#include "queue.h"
#include "functions.h"
#include "stdio.h"
#include "strategy.h"
#include <stdlib.h>

void threadPerThreadHandler(Queue *messages, Queue *results) {
    while(1){
        TMessage *tMessage = (TMessage *)removeFromQueue(messages);

        if( tMessage != NULL ) {
            ThreadArgs *threadArgs = (ThreadArgs *)malloc(sizeof(ThreadArgs));
            threadArgs->results = results;
            threadArgs->tMessage = tMessage;

            printf("next message %d \n", tMessage->Type);

            int result;
            pthread_t taskHandlerId;

            if (tMessage->Type == FIBONACCI)
                result = pthread_create(&taskHandlerId, NULL, fibbonachiThread, threadArgs);
            else if (tMessage->Type == POW)
                result = pthread_create(&taskHandlerId, NULL, powThread, threadArgs);
            else if (tMessage->Type == BUBBLE_SORT_UINT64)
                result = pthread_create(&taskHandlerId, NULL, bubbleSortThread, threadArgs);
            else if (tMessage->Type == STOP) {
                break;
            }
        }
    }

}

void threadPerTaskHandler(Queue *messages, Queue *results) {
    pthread_t fibbThreadId, powThreadId, sortThreadId;
    Queue *fibbQueue = createQueue();
    Queue *powQueue = createQueue();
    Queue *sortQueue = createQueue();

    TaskArgs *fibbArgs = (TaskArgs *)malloc(sizeof(ThreadArgs));
    fibbArgs->results = results;
    fibbArgs->messages = fibbQueue;
    fibbArgs->handler = fibbonachiThread;

    TaskArgs *powArgs = (TaskArgs *)malloc(sizeof(ThreadArgs));
    powArgs->results = results;
    powArgs->messages = powQueue;
    powArgs->handler = powThread;

    TaskArgs *sortArgs = (TaskArgs *)malloc(sizeof(ThreadArgs));
    sortArgs->results = results;
    sortArgs->messages = sortQueue;
    sortArgs->handler = bubbleSortThread;

    pthread_create(&fibbThreadId, NULL, taskThreadWrapper, fibbArgs);
    pthread_create(&powThreadId, NULL, taskThreadWrapper, powArgs);
    pthread_create(&sortThreadId, NULL, taskThreadWrapper, sortArgs);

    while(1){
        TMessage *tMessage = (TMessage *)removeFromQueue(messages);
        if( tMessage != NULL ) {
            if (tMessage->Type == FIBONACCI)
                addToQueue(fibbQueue, tMessage);
            else if (tMessage->Type == POW)
                addToQueue(powQueue, tMessage);
            else if (tMessage->Type == BUBBLE_SORT_UINT64)
                addToQueue(sortQueue, tMessage);
            else if (tMessage->Type == STOP) {
                addToQueue(fibbQueue, tMessage);
                addToQueue(powQueue, tMessage);
                addToQueue(sortQueue, tMessage);
                break;
            }
        }
    }

}

void *taskThreadWrapper(void * _args){
    TaskArgs *taskArgs = (TaskArgs *)_args;

    while(1){
        TMessage *tMessage = (TMessage *)removeFromQueue(taskArgs->messages);

        if( tMessage != NULL ) {
            if(tMessage->Type == 3)
                break;

            ThreadArgs *threadArgs = (ThreadArgs *)malloc(sizeof(ThreadArgs));
            threadArgs->results = taskArgs->results;
            threadArgs->tMessage = tMessage;
            taskArgs->handler(threadArgs);
        }
    }
}