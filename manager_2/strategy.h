#include "queue.h"

void threadPerThreadHandler(Queue *messages, Queue *result);
void threadPerTaskHandler(Queue *messages, Queue *results);
void *taskThreadWrapper(void * _args);
