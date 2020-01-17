#include <sys/time.h>
#include "../common/queue.h"
#include "string.h"
#include "stdio.h"
#include "fileWriter.h"

void decrementCounter(int *counter, pthread_mutex_t* mutex){
    pthread_mutex_lock(mutex);
    *counter = *counter - 1;
    pthread_mutex_unlock(mutex);
}

void *writer(void* _args) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    FILE* fin = fopen("./manager_3/results/results.txt", "w");
    FILE *writerStatistics = fopen("./manager_3/results/writer.txt", "w");

    if(fin == NULL)
        return NULL;

    IOArgs *args = (IOArgs *)_args;
    pthread_mutex_t resultsMutex;
    pthread_mutex_init(&resultsMutex, NULL);
    pthread_mutex_t statisticsMutex;
    pthread_mutex_init(&statisticsMutex, NULL);

    int i = 0;

    while(1) {
        struct timespec startTime, endTime, queueEndTime;
        long int duration, queueDuration;

        clock_gettime(CLOCK_REALTIME, &startTime);
        Message *taskResult = (Message *)removeFromQueue(args->q);

        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        if(taskResult == NULL) {

            pthread_mutex_lock(args->mutex);
            pthread_cond_wait(args->condVar, args->mutex);
            pthread_mutex_unlock(args->mutex);

            pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
            continue;
        } else {
            clock_gettime(CLOCK_REALTIME, &queueEndTime);
            queueDuration = convertToMicroSeconds(queueEndTime) - convertToMicroSeconds(taskResult->start);
            writeToFileSingle((FILE *)args->queueStatistics->data, args->queueStatistics->mutex, queueDuration);

            decrementCounter((int *)args->counter->data, args->counter->mutex);
            pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        }

        TMessage *result = taskResult->message;
        if(result->Type == STOP)
            break;

        switch(result->Type){
                case 0:
                case 1: {
                    writeToFileSingle(fin, &resultsMutex, (long)result->Data[0]);
                    break;
                }
                default:
                    writeToFileMultiple(fin, &resultsMutex, result->Size, (long *)result->Data);
        }
        i++;

        clock_gettime(CLOCK_REALTIME, &endTime);
        duration = convertToMicroSeconds(endTime) - convertToMicroSeconds(startTime);
        writeToFileSingle(writerStatistics, &statisticsMutex, (long)duration);
    }

    fclose(fin);
    fclose(writerStatistics);
}