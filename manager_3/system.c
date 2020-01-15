#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "io/fileWriter.h"

void *writeSystemStatistics(void * _args){
    FILE* statistics = fopen("./manager_3/results/system.txt", "w");
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    struct timespec startTime = *(struct timespec *)_args;
    long start = startTime.tv_sec * 1000000 + startTime.tv_nsec / 1000;

    struct timespec endTime;
    long duration;
    int interval = 1;

    while(1){
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

        sleep(interval);

        clock_gettime(CLOCK_REALTIME, &endTime);
        long end = endTime.tv_sec * 1000000 + endTime.tv_nsec / 1000;

        duration = end - start;
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);

        writeToFileSingle(statistics, &mutex, duration);
    }
}