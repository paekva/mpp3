#include <stdio.h>
#include "common/types.h"
#include "io/reader.h"
#include "common/queue.h"
#include "parser.h"
#include <stdlib.h>

int main(int argc, char* argv[]){
    pthread_t readerID, writerID;

    // Params params = getOptions(argc, argv);
    Queue *messages = createQueue();

    // start reading thread
    pthread_create(&readerID, NULL, reader, messages);
    // pthread_create(&writerID, NULL, reader, messages);

    pthread_join(readerID, NULL);
    // pthread_join(writerID, NULL);

    printf("finsihs");
    return 0;
}
