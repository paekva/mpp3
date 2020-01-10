#include "../common/queue.h"
#include "protobufHandler.h"
#include <stdio.h>

void *reader(void* _args) {
    IOArgs* args = (IOArgs *) _args;
    getMessages(args);
    return NULL;
}