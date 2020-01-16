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
        struct timespec startTime, endTime;
        long int duration;

        clock_gettime(CLOCK_REALTIME, &startTime);
        TMessage *result = (TMessage *)removeFromQueue(args->q);

        if(result == NULL) {
            // wait for condition
            pthread_mutex_lock(args->mutex);
            pthread_cond_wait(args->condVar, args->mutex);
            pthread_mutex_unlock(args->mutex);
            continue;
        }

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        decrementCounter(args->counter, args->counterMutex);

        if(result->Type == STOP)
            break;

        switch(result->Type){
                case 0:
                case 1: {
                    writeToFileSingle(fin, &resultsMutex, result->Data[0]);
                    break;
                }
                default:
                    writeToFileMultiple(fin, &resultsMutex, result->Size, result->Data);
        }
        i++;
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);

        clock_gettime(CLOCK_REALTIME, &endTime);
        duration=1000000*(endTime.tv_sec - startTime.tv_sec)+(endTime.tv_nsec - startTime.tv_nsec)/1000;
        writeToFileSingle(writerStatistics, &statisticsMutex, duration);
    }

    fclose(fin);
    fclose(writerStatistics);
}