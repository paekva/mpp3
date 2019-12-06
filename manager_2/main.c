#include <stdio.h>
#include "protobufHandler.h"
#include "queue.h"

int main() {
    Queue *tryout = createQueue();

    getMessages(tryout);
    printf("size: %d\n", getQueueSize(tryout));

    return 0;
}
