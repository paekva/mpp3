#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "io/fileWriter.h"
#include "common/types.h"
#include "common/queue.h"

void *writeSystemStatistics(void * _args){
    FILE* statistics = fopen("./manager_3/results/system.txt", "w");
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    ReportArgs *args = (ReportArgs*) _args;

    struct timespec startTime = *args->startTime;
    long start = startTime.tv_sec * 1000000 + startTime.tv_nsec / 1000;

    struct timespec endTime;
    long duration;
    int interval = args->interval / 1000;

    while(1){
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

        sleep(interval);

        clock_gettime(CLOCK_REALTIME, &endTime);
        long end = endTime.tv_sec * 1000000 + endTime.tv_nsec / 1000;
        duration = end - start;

        pthread_mutex_lock(args->counterMutex);
        int queueSize = *args->counter;
        pthread_mutex_unlock(args->counterMutex);

        int systemInfo[] = {duration, queueSize};
        printf("system info: %d %d \n", duration, queueSize);

        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);

        writeToFileMultiple(statistics, &mutex, 2, &systemInfo);
    }
}