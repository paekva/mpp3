#include <sys/time.h>
#include "../common/queue.h"
#include "string.h"
#include "stdio.h"

void *writer(void* _args) {
    IOArgs *writer = (IOArgs *)_args;

    FILE* fin = fopen("../results.txt", "w");
    if(fin == NULL)
        return NULL;

    FILE *readerStats = fopen("../readerStats.txt", "w");
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
        printf("TYPE -> %d \n", result->Type);
        switch(result->Type){
                case 0:
                case 1: {
                    printf("result pow/fibb\n");
                    fprintf(fin,"result %hhu\n", result->Data[0]);
                    break;
                }
                case 2:{
                    printf("result bubble %lu\n", result->Size);
                    fprintf(fin,"result %hhu\n", result->Data[0]);
                    break;
                }
                default:
                    return NULL;
        }
        i++;
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);

        clock_gettime(CLOCK_REALTIME, &endTime);
        duration=1000000000*(endTime.tv_sec - startTime.tv_sec)+(endTime.tv_nsec - startTime.tv_nsec);
        fprintf (readerStats, "%ld\n", duration);
    }

    fclose(fin);
    fclose(readerStats);
}