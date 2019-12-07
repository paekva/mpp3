#include <stdio.h>
#include "queue.h"
#include "parser.h"
#include "reader.h"
#include "writer.h"
#include "strategy.h"

int main(int argc, char* argv[]) {
    pthread_t readerID, reporterID, writerID;

    Params params = getOptions(argc, argv);
    Queue *messages = createQueue();
    Queue *results = createQueue();

    // start reading thread
    pthread_create(&readerID, NULL, reader, messages);

    // start writing thread
    pthread_create(&writerID, NULL, writer, results);

    if (params.strategy == PER_THREAD)
        threadPerThreadHandler(messages, results);
    else if (params.strategy == PER_TASK) {
        threadPerTaskHandler(messages, results);
        printf("PER_TASK\n");
    }
    else {
        printf("THREAD_POOL\n");
    }

    pthread_join(readerID, NULL);
    pthread_join(writerID, NULL);
    printf("after writer");
    return 0;
}
