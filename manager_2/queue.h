#pragma once

#include "types.h"

typedef struct QueueNode
{
    TMessage *value;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode* head;
    QueueNode* tail;
} Queue;

TMessage removeFromQueue(Queue* q);
void addToQueue(Queue* q, TMessage* newValue);
Queue *createQueue();
void destroyQueue(Queue **queue);
int getQueueSize(Queue *queue);