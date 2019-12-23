#include "queue.h"
#include "protobufHandler.h"
#include <stdio.h>

void *reader(void* _args) {
    ReaderArgs* args = (ReaderArgs *) _args;
    getMessages(args->messages);
    return NULL;
}