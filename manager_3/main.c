#include <stdio.h>
#include "types.h"
#include "reader.h"
#include "queue.h"
#include "parser.h"
#include <stdlib.h>

int main(int argc, char* argv[]){
    pthread_t readerID, reporterID, writerID;

    // Params params = getOptions(argc, argv);
    Queue *messages = createQueue();
    Queue *readTime = createQueue();

    ReaderArgs *readerArgs = (ReaderArgs *)malloc(sizeof(ReaderArgs));
    readerArgs->messages = messages;
    readerArgs->reporter = readTime;

    // start reading thread
    pthread_create(&readerID, NULL, reader, readerArgs);
    pthread_join(readerID, NULL);
    return 0;
}
