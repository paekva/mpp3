#pragma once
#include <pthread.h>
#include "types.h"

void* removeFromQueue(Queue* q);
void addToQueue(Queue* q, void* newValue);
Queue *createQueue();
void destroyQueue(Queue **queue);
int getQueueSize(Queue *queue);