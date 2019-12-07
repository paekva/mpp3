#include <sys/time.h>
#include "queue.h"
#include "stdio.h"

void *writer(void* _args) {
    WriterArgs *args = (WriterArgs *)_args;
    FILE* fin = fopen("../results.txt", "w");
    int i = 0;

    while(1){
        struct timespec startTime;
        struct timespec endTime;
        clock_gettime(CLOCK_REALTIME, &startTime);

        char *message = removeFromQueue(args->results);

        if(message != NULL) {
            fprintf(fin,"result %s\n", message);
            i++;

            clock_gettime(CLOCK_REALTIME, &endTime);
            long result = endTime.tv_nsec - startTime.tv_nsec;

            // addToQueue(args->reporter, result);
            // printf("%d \n", getQueueSize(args->reporter));
        }

        if(i>30)
            break;
    }

    fclose(fin);
}