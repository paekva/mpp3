#include <stdlib.h>
#include <stdio.h>
#include "common/types.h"
#include "common/queue.h"
#include "common/functions.h"

void perThreadHandler(IOArgs *_reader, Queue *results) {
    IOArgs *reader = (IOArgs *)_reader;
    while(1){
        TMessage *tMessage = (TMessage *)removeFromQueue(reader->q);
        if( tMessage != NULL ) {
            if (tMessage->Type == STOP) {
                addToQueue(results, "STOP");
                break;
            }

            ThreadArgs *threadArgs = (ThreadArgs *)malloc(sizeof(ThreadArgs));
            threadArgs->results = results;
            threadArgs->tMessage = tMessage;

            pthread_t taskHandlerId;

            if (tMessage->Type == FIBONACCI)
                pthread_create(&taskHandlerId, NULL, fibbonachiThread, threadArgs);
            else if (tMessage->Type == POW)
                pthread_create(&taskHandlerId, NULL, powThread, threadArgs);
            else if (tMessage->Type == BUBBLE_SORT_UINT64)
                pthread_create(&taskHandlerId, NULL, bubbleSortThread, threadArgs);
        }
    }
}