#include "types.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void addToQueue(Queue* q, TMessage* newValue){
    if(q == NULL) {
        return;
    }
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->value = newValue;
    newNode->next = NULL;

    pthread_mutex_lock(&q->mutexId);
    QueueNode *tail = q->tail;
    if(tail == NULL){
        // empty queue
        q->tail = newNode;
        q->head = newNode;
    } else {
        tail->next = newNode;
        q->tail = newNode;
    }
    pthread_mutex_unlock(&q->mutexId);
}

void addToQueueWrapper(Queue* q, TMessage* newValue){
    addToQueue(q, newValue);
}

TMessage removeFromQueue(Queue* q){
    TMessage returnValue = {};
    if(q == NULL){
        return returnValue;
    }

    pthread_mutex_lock(&q->mutexId);
    if(q->head != NULL && q->tail != NULL){
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
    pthread_mutex_unlock(&q->mutexId);
    return returnValue;
}

int getQueueSize(Queue *queue) {
    if(queue == NULL){
        return -1;
    }

    pthread_mutex_lock(&queue->mutexId);
    QueueNode* current = queue->head;
    int count = 0;
    while(current != NULL){
        current = current->next;
        count ++;
    }

    pthread_mutex_unlock(&queue->mutexId);
    return count;
}

Queue *createQueue(){
    Queue* newQueue = (Queue *)malloc(sizeof(Queue));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    pthread_mutex_init(&newQueue->mutexId, NULL);
    return newQueue;
}

void destroyQueue(Queue **queue){
    if(queue != NULL) {
        int size = getQueueSize(*queue);
        while (size != 0) {
            removeFromQueue(*queue);
            size = getQueueSize(*queue);
        }

        pthread_mutex_destroy(&(*queue)->mutexId);
        free(*queue);
        *queue = NULL;
    }
}