#include <stdlib.h>
#include "common/types.h"
#include "common/queue.h"

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
                addToQueue(results, "STOP");
                break;
            }
        }
    }

}