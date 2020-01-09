#include <sys/time.h>
#include "../common/queue.h"
#include "string.h"
#include "stdio.h"

void *writer(void* _args) {
    Queue *results = (Queue *)_args;

    FILE* fin = fopen("../results.txt", "w");
    if(fin == NULL)
        return NULL;

    FILE *readerStats = fopen("../readerStats.txt", "w");
    int i = 0;

    while(1) {
        struct timespec startTime, endTime;
        long int duration;

        clock_gettime(CLOCK_REALTIME, &startTime);
        char *message = removeFromQueue(results);

        if(message != NULL) {
            fprintf(fin,"result %s\n", message);
            i++;

            clock_gettime(CLOCK_REALTIME, &endTime);;
            duration=1000000000*(endTime.tv_sec - startTime.tv_sec)+(endTime.tv_nsec - startTime.tv_nsec);
            fprintf (readerStats, "%ld\n", duration);

            if(strcmp(message, "STOP") == 0)
                break;
        }
    }

    fclose(fin);
    fclose(readerStats);
}