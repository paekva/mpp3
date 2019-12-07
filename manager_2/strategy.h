#include "queue.h"

void threadPerThreadHandler(Queue *messages, Queue *result);
void threadPerTaskHandler(Queue *messages, Queue *results);
void *taskThreadWrapper(void * _args);
void threadPoolHandler(int count, Queue *messages, Queue *results);
void * poolThreadWrapper(void * _args);
