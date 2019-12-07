#include <stdio.h>
#include "types.h"
#include "queue.h"

void *reporter(void *_args){
    ReportingArgs * args = (ReportingArgs *)_args;
    FILE* fin = fopen("../reportWriter.txt", "w");
    int i = 0;

    while(args->writeTime != NULL){
        char *message = removeFromQueue(args->writeTime);

        if(message != NULL) {
            fprintf(fin,"writer time^ %s\n", message);
            i++;
        }

        if(i>30)
            break;
    }

    fclose(fin);
}