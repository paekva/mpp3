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
    FILE* systemStatistics = fopen("./manager_3/results/system.txt", "w");

    pthread_t readerID, writerID, systemID;
    pthread_cond_t readerC, writerC;
    pthread_mutex_t readerM, writerM, counterM;
    int counter = 0;

    pthread_mutex_init(&readerM, NULL);
    pthread_mutex_init(&writerM, NULL);
    pthread_mutex_init(&counterM, NULL);
    pthread_cond_init(&readerC, NULL);
    pthread_cond_init(&writerC, NULL);

    Queue *messages = createQueue();
    Queue *results = createQueue();
    Params params = getOptions(argc, argv);


    IOArgs readerArgs = {
            messages,
            &readerC,
            &readerM,
            &counter,
            &counterM
    };
    IOArgs writerArgs = {
            results,
            &writerC,
            &writerM,
            &counter,
            &counterM
    };
    ReportArgs reportArgs = {
            &startTime,
            params.msInterval,
            &counter,
            &counterM,
            systemStatistics
    };

    pthread_create(&readerID, NULL, reader, &readerArgs);
    pthread_create(&writerID, NULL, writer, &writerArgs);
    pthread_create(&systemID, NULL, writeSystemStatistics, &reportArgs);


    if (params.strategy == PER_THREAD)
        perThreadHandler(&readerArgs, &writerArgs, handlerStatistics);
    else if (params.strategy == PER_TASK) printf("PER_TASK");
        // threadPerTaskHandler(messages, results);
    else printf("THREAD_POOL");
        // threadPoolHandler(params.threadsCount, messages, results);


    pthread_join(readerID, NULL);
    pthread_cancel(writerID);
    pthread_cancel(systemID);
    fclose(handlerStatistics);
    fclose(systemStatistics);

    return 0;
}
