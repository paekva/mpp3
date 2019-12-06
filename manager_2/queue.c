#include "types.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void addToQueue(Queue* q, TMessage* newValue){
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->value = newValue;
    newNode->next = NULL;

    QueueNode *tail = q->tail;
    if(tail == NULL){
        // empty queue
        q->tail = newNode;
        q->head = newNode;
    } else {
        tail->next = newNode;
        q->tail = newNode;
    }
}

TMessage removeFromQueue(Queue* q){
    TMessage returnValue = {};
    if(q != NULL && q->head != NULL && q->tail != NULL){
        // not empty

        QueueNode *removedNode = q->head;
        q->head = removedNode->next;
        if(q->head == NULL){
            // it was last element
            q->tail = NULL;
        }

        returnValue = *(removedNode->value);
        free(removedNode);
    }
    return returnValue;
}

Queue *createQueue(){
    Queue* newQueue = (Queue *)malloc(sizeof(Queue));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    return newQueue;
}

void destroyQueue(Queue **queue){
    int size = getQueueSize(*queue);
    while(size != 0){
        removeFromQueue(*queue);
        size = getQueueSize(*queue);
    }

    free(*queue);
    *queue = NULL;
}

int getQueueSize(Queue *queue) {
    if(queue == NULL){
        return -1;
    }

    QueueNode* current = queue->head;
    int count = 0;
    while(current != NULL){
        current = current->next;
        count ++;
    }
    return count;
}