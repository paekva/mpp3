#include "queue.h"
#include "protobufHandler.h"
#include <stdio.h>

void *reader(void* _args) {
    Queue* messages = (Queue *) _args;
    getMessages(messages);
    printf("size: %d\n", getQueueSize(messages));
    return NULL;
}