#include <sys/time.h>
#include "../common/queue.h"
#include "string.h"
#include "stdio.h"
#include "fileWriter.h"

void writeToFileMultiple(FILE* fin, pthread_mutex_t* mutex, int size, uint8_t message){
    pthread_mutex_lock(mutex);
    /*
    for(int j =0;j<size; j++){
        fprintf(fin,"%hhu ", message);
    }
    fprintf(fin,"\n");
    fflush(fin);
     */
    pthread_mutex_unlock(mutex);
}

void *writer(void* _args) {
    IOArgs *writer = (IOArgs *)_args;

    pthread_mutex_t resultsMutex;
    pthread_mutex_init(&resultsMutex, NULL);
    FILE* fin = fopen("./manager_3/results/results.txt", "w");
    if(fin == NULL)
        return NULL;

    FILE *writerInfo = fopen("./manager_3/results/writer.txt", "w");
    pthread_mutex_t statisticsMutex;
    pthread_mutex_init(&statisticsMutex, NULL);

    int i = 0;

    while(1) {
        struct timespec startTime, endTime;
        long int duration;

        clock_gettime(CLOCK_REALTIME, &startTime);
        TMessage *result = (TMessage *)removeFromQueue(writer->q);

        if(result == NULL) {
            // wait for condition
            pthread_mutex_lock(writer->mutex);
            pthread_cond_wait(writer->condVar, writer->mutex);
            pthread_mutex_unlock(writer->mutex);
            continue;
        }

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        if(result->Type == STOP)
            break;

        switch(result->Type){
                case 0:
                case 1: {
                    writeToFileSingle(fin, &resultsMutex, result->Data[0]);
                    break;
                }
                default:
                    writeToFileMultiple(fin, &resultsMutex, result->Size, result->Data[0]);
        }
        i++;
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);

        clock_gettime(CLOCK_REALTIME, &endTime);
        duration=1000000000*(endTime.tv_sec - startTime.tv_sec)+(endTime.tv_nsec - startTime.tv_nsec);
        writeToFileSingle(writerInfo, &statisticsMutex, duration);
    }

    fclose(fin);
    fclose(writerInfo);
}