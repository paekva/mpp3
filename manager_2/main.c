#include <stdio.h>
#include "protobufHandler.h"
#include "queue.h"

int main() {
    char message;

    getMessages(&message);
    printf("%c Hello, World! \n", message);

    Queue *tryout = createQueue();
    TMessage m1 = {
            1,
            1,
            1
    };
    TMessage m2 = {
            2,
            2,
            2
    };
    TMessage m3 = {
            3,
            3,
            3
    };

    addToQueue(tryout, &m1);
    printf("size: %d\n", getQueueSize(tryout));
    addToQueue(tryout, &m2);
    printf("size: %d\n", getQueueSize(tryout));
    addToQueue(tryout, &m3);
    printf("size: %d\n", getQueueSize(tryout));

    destroyQueue(&tryout);
    printf("size: %d\n", getQueueSize(tryout));
    return 0;
}
