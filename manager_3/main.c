#include <stdio.h>
#include "common/types.h"
#include "io/reader.h"
#include "common/queue.h"
#include "parser.h"
#include "io/writer.h"
#include "strategy.h"
#include "system.h"
#include <stdlib.h>

int main(int argc, char* argv[]){
    struct timespec startTime;
    clock_gettime(CLOCK_REALTIME, &startTime);

    FILE* handlerStatistics = fopen("./manager_3/results/handler.txt", "w");

    pthread_t readerID, writerID, systemID;
    pthread_cond_t readerC, writerC;
    pthread_mutex_t readerM, writerM;

    pthread_mutex_init(&readerM, NULL);
    pthread_mutex_init(&writerM, NULL);
    pthread_cond_init(&readerC, NULL);
    pthread_cond_init(&writerC, NULL);

    Queue *messages = createQueue();
    Queue *results = createQueue();
    Params params = getOptions(argc, argv);


    IOArgs readerArgs = {
            messages,
            &readerC,
            &readerM
    };
    IOArgs writerArgs = {
            results,
            &writerC,
            &writerM
    };

    pthread_create(&readerID, NULL, reader, &readerArgs);
    pthread_create(&writerID, NULL, writer, &writerArgs);
    pthread_create(&systemID, NULL, writeSystemStatistics, &startTime);


    if (params.strategy == PER_THREAD)
        perThreadHandler(&readerArgs, &writerArgs, handlerStatistics);
    else if (params.strategy == PER_TASK) printf("PER_TASK");
        // threadPerTaskHandler(messages, results);
    else printf("THREAD_POOL");
        // threadPoolHandler(params.threadsCount, messages, results);


    pthread_join(readerID, NULL);
    pthread_cancel(writerID);
    pthread_join(writerID, NULL);
    pthread_cancel(systemID);
    fclose(handlerStatistics);

    return 0;
}
