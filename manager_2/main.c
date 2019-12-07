#include <stdio.h>
#include "queue.h"
#include "parser.h"
#include "reader.h"
#include "writer.h"
#include "strategy.h"
#include <stdlib.h>
#include "reporter.h"

int main(int argc, char* argv[]) {
    pthread_t readerID, reporterID, writerID;

    Params params = getOptions(argc, argv);
    Queue *messages = createQueue();
    Queue *results = createQueue();

    Queue * queueWaitTime = createQueue();
    Queue * writeTime = createQueue();
    Queue * algTime = createQueue();
    Queue * readTime = createQueue();

    ReportingArgs * reportingArgs = (ReportingArgs *)malloc(sizeof(ReportingArgs));
    reportingArgs->queueWaitTime = queueWaitTime;
    reportingArgs->writeTime = writeTime;
    reportingArgs->algTime = algTime;
    reportingArgs->readTime = readTime;

    ReaderArgs *readerArgs = (ReaderArgs *)malloc(sizeof(ReaderArgs));
    readerArgs->messages = messages;
    readerArgs->reporter = readTime;

    WriterArgs *writerArgs = (WriterArgs *)malloc(sizeof(WriterArgs));
    writerArgs->results = results;
    writerArgs->reporter = writeTime;

    // start reading thread
    pthread_create(&readerID, NULL, reader, readerArgs);

    // start writing thread
    pthread_create(&writerID, NULL, writer, writerArgs);

    // start reporter thread
    pthread_create(&reporterID, NULL, reporter, reportingArgs);

    if (params.strategy == PER_THREAD)
        threadPerThreadHandler(messages, results);
    else if (params.strategy == PER_TASK)
        threadPerTaskHandler(messages, results);
    else
        threadPoolHandler(params.threadsCount, messages, results);

    pthread_join(readerID, NULL);
    pthread_join(writerID, NULL);

    return 0;
}
