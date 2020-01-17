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
    FILE* queueStatisticsF = fopen("./manager_3/results/queue.txt", "w");
    FILE* systemStatistics = fopen("./manager_3/results/system.txt", "w");

    pthread_t readerID, writerID, systemID;
    pthread_cond_t readerC, writerC;
    pthread_mutex_t readerM, writerM, counterM, queueStatisticsM;
    int counter = 0;

    pthread_mutex_init(&readerM, NULL);
    pthread_mutex_init(&writerM, NULL);
    pthread_mutex_init(&counterM, NULL);
    pthread_mutex_init(&queueStatisticsM, NULL);
    pthread_cond_init(&readerC, NULL);
    pthread_cond_init(&writerC, NULL);

    Queue *messages = createQueue();
    Queue *results = createQueue();
    Params params = getOptions(argc, argv);

    Data queueStatistics = {
            &queueStatisticsM,
            queueStatisticsF,
    };
    Data counterData = {
            &counterM,
            &counter
    };
    IOArgs readerArgs = {
            messages,
            &readerC,
            &readerM,
            &counterData
    };
    IOArgs writerArgs = {
            results,
            &writerC,
            &writerM,
            &counterData,
            &queueStatistics
    };
    ReportArgs reportArgs = {
            &startTime,
            params.msInterval,
            &counterData,
            systemStatistics
    };

    pthread_create(&readerID, NULL, reader, &readerArgs);
    pthread_create(&writerID, NULL, writer, &writerArgs);
    pthread_create(&systemID, NULL, writeSystemStatistics, &reportArgs);


    if (params.strategy == PER_THREAD)
        perThreadHandler(&readerArgs, &writerArgs, handlerStatistics, &queueStatistics);
    else if (params.strategy == PER_TASK) printf("PER_TASK");
        // threadPerTaskHandler(messages, results);
    else printf("THREAD_POOL");
        // threadPoolHandler(params.threadsCount, messages, results);


    pthread_join(readerID, NULL);
    pthread_cancel(writerID);
    pthread_cancel(systemID);
    fclose(handlerStatistics);
    fclose(systemStatistics);
    fclose(queueStatisticsF);

    return 0;
}
