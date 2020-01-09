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
    Queue *messages = createQueue();
    Queue *results = createQueue();
    Params params = getOptions(argc, argv);

    pthread_create(&readerID, NULL, reader, messages);
    // pthread_create(&writerID, NULL, writer, results);


    // TODO: -------------------LOGIC-------------------------------
    // TODO: -------------------------------------------------------

    if (params.strategy == PER_THREAD)
        printf("PER_THREAD");
        // threadPerThreadHandler(messages, results);
    else if (params.strategy == PER_TASK)
        printf("PER_TASK");
        // threadPerTaskHandler(messages, results);
    else
        printf("THREAD_POOL");
        // threadPoolHandler(params.threadsCount, messages, results);

    // TODO: -------------------------------------------------------
    // TODO: -------------------LOGIC-------------------------------



    pthread_join(readerID, NULL);
    // pthread_join(writerID, NULL);

    printf("finsihs\n");
    return 0;
}
