#include <stdio.h>
#include "common/types.h"
#include "io/reader.h"
#include "common/queue.h"
#include "parser.h"
#include "io/writer.h"
#include "strategy.h"
#include <stdlib.h>

int main(int argc, char* argv[]){
    pthread_t readerID, writerID;
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


    // TODO: -------------------LOGIC-------------------------------
    // TODO: -------------------------------------------------------

    if (params.strategy == PER_THREAD)
        perThreadHandler(&readerArgs, &writerArgs);
    else if (params.strategy == PER_TASK)
        printf("PER_TASK");
        // threadPerTaskHandler(messages, results);
    else
        printf("THREAD_POOL");
        // threadPoolHandler(params.threadsCount, messages, results);

    // TODO: -------------------------------------------------------
    // TODO: -------------------LOGIC-------------------------------

    pthread_join(readerID, NULL);
    printf("DONE READER\n");
    pthread_cancel(writerID);
    pthread_join(writerID, NULL);

    return 0;
}
