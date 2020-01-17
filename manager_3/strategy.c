#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "common/types.h"
#include "common/queue.h"
#include "common/functions.h"
#include "io/fileWriter.h"

void *chooseHandlerFunc(void *_args){
    struct timespec startTime;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

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

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    Message* result = malloc(sizeof(Message));
    result->message = taskResult;
    clock_gettime (CLOCK_REALTIME, &startTime);
    result->start = startTime;

    addToQueue(args->writer->q, result);

    pthread_mutex_lock(args->writer->mutex);
    pthread_cond_signal(args->writer->condVar);
    pthread_mutex_unlock(args->writer->mutex);

    return NULL;
}

void perThreadHandler(IOArgs *reader, IOArgs *writer, FILE *statistics, Data* queueStatistics) {
    // Queue *ids = createQueue();
    struct timespec queueEndTime;
    long duration;

    while(1) {
        Message *messageInfo = (Message *)removeFromQueue(reader->q);

        if(messageInfo == NULL) {
            // wait for condition
            pthread_mutex_lock(reader->mutex);
            pthread_cond_wait(reader->condVar, reader->mutex);
            pthread_mutex_unlock(reader->mutex);
            continue;
        }

        clock_gettime (CLOCK_REALTIME, &queueEndTime);
        duration = convertToMicroSeconds(queueEndTime) - convertToMicroSeconds(messageInfo->start);
        writeToFileSingle(queueStatistics->data, queueStatistics->mutex, duration);

        TMessage *tMessage = messageInfo->message;
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
        threadArgs->statistics = statistics;

        pthread_create(pointer, NULL, chooseHandlerFunc, threadArgs);
    }
}