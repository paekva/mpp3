#include "../common/queue.h"
#include "protobufHandler.h"
#include <stdio.h>

void *reader(void* _args) {
    Queue* messages = (Queue *) _args;
    getMessages(messages);
    return NULL;
}