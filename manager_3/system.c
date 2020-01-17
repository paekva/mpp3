#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "io/fileWriter.h"
#include "common/types.h"

void *writeSystemStatistics(void * _args){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    ReportArgs *args = (ReportArgs*) _args;
    int interval = args->interval / 1000;

    long start = convertToMicroSeconds(*args->startTime);
    struct timespec endTime;
    long duration;


    while(1){
        sleep(interval);

        clock_gettime(CLOCK_REALTIME, &endTime);
        long end = convertToMicroSeconds(endTime);
        duration = end - start;

        pthread_mutex_lock(args->counter->mutex);
        int queueSize = *(int *)args->counter->data;
        pthread_mutex_unlock(args->counter->mutex);

        long systemInfo[] = {duration, (long)queueSize};
        writeToFileMultiple((FILE *)args->reportFile, &mutex, 2, (long *)&systemInfo);
    }
}