#include "queue.h"
#include "message.pb.h"


typedef struct {
    TMessage *message;
    TMessage *next;
} Message;

typedef struct {
    Message *start;
    Message *end;
} Queue;

Queue *createQueue(){
    return (Queue*)malloc(sizeof(Queue));
}

void setQueueItem(Queue *q, Message *msg){
    if(q->start)
}