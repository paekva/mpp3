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

    TaskArgs *fibbArgs = (TaskArgs *)malloc(sizeof(TaskArgs));
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

void threadPoolHandler(int count, Queue *messages, Queue *results) {
    pthread_t *threadIds = (pthread_t *)malloc(count * sizeof(pthread_t));

    for(int i=0; i< count; i++){
        pthread_t thread;
        threadIds[i] = thread;

        TaskArgs *taskArgs = (TaskArgs *)malloc(sizeof(TaskArgs));
        taskArgs->results = results;
        taskArgs->messages = messages;

        pthread_create(&threadIds[i], NULL, poolThreadWrapper, taskArgs);
    }
}

void * poolThreadWrapper(void * _args){
    TaskArgs *taskArgs = (TaskArgs*)_args;

    while(1){
        TMessage *tMessage = (TMessage *)removeFromQueue(taskArgs->messages);

        if( tMessage != NULL ) {
            ThreadArgs *threadArgs = (ThreadArgs *)malloc(sizeof(ThreadArgs));
            threadArgs->results = taskArgs->results;
            threadArgs->tMessage = tMessage;

            if (tMessage->Type == FIBONACCI)
                fibbonachiThread(threadArgs);
            else if (tMessage->Type == POW)
                powThread(threadArgs);
            else if (tMessage->Type == BUBBLE_SORT_UINT64)
                bubbleSortThread(threadArgs);
            else if (tMessage->Type == STOP) {
                break;
            }
        }
    }
}