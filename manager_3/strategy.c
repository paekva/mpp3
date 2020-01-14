#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "common/types.h"
#include "common/queue.h"
#include "common/functions.h"

void *chooseHandlerFunc(void *_args){
    ThreadArgs *args = (ThreadArgs *)_args;

    TMessage* taskResult = malloc(sizeof(TMessage));
    taskResult->Type = args->tMessage->Type;
    taskResult->Size = 0;
    taskResult->Data = NULL;

    if (args->tMessage->Type == FIBONACCI)
        (*taskResult).Data = fibbonachiTask(args);
    else if (args->tMessage->Type == POW)
        (*taskResult).Data = powTask(args);
    else {
        (*taskResult).Data = bubbleSortTask(args);
        (*taskResult).Size = args->tMessage->Size;
    }

    addToQueue(args->writer->q, taskResult);
    pthread_cond_signal(args->writer->condVar);

    return NULL;
}

void perThreadHandler(IOArgs *reader, IOArgs *writer) {
    // Queue *ids = createQueue();

    while(1) {
        TMessage *tMessage = (TMessage *)removeFromQueue(reader->q);

        if(tMessage == NULL) {
            // wait for condition
            pthread_mutex_lock(reader->mutex);
            pthread_cond_wait(reader->condVar, reader->mutex);
            pthread_mutex_unlock(reader->mutex);
            continue;
        }

        if (tMessage->Type == STOP) {
            /* TODO: FIX
            int threadCount = getQueueSize(ids);
            for(int i= 0;i < threadCount; i++){
                pthread_t *id= removeFromQueue(ids);
                printf("closing thread %lu ... ", *id);
                pthread_cancel(*id);
                printf("closed\n");
            }
            */
            return;
        }

        pthread_t taskHandlerId;
        pthread_t *pointer = &taskHandlerId;
        // addToQueue(ids, pointer);

        ThreadArgs *threadArgs = (ThreadArgs *)malloc(sizeof(ThreadArgs));
        threadArgs->writer = writer;
        threadArgs->tMessage = tMessage;

        pthread_create(pointer, NULL, chooseHandlerFunc, threadArgs);
    }
}