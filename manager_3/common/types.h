#pragma once
#include <stdint.h>
#include <pthread.h>

typedef struct {
    uint8_t Type;
    uint64_t Size;
    uint8_t *Data;
} TMessage;

typedef enum
{
    FIBONACCI,
    POW,
    BUBBLE_SORT_UINT64,
    STOP
} EType;

typedef enum
{
    PER_THREAD,
    PER_TASK,
    THREAD_POOL
} Strategy;

typedef struct {
    Strategy strategy;
    uint8_t threadsCount;
    uint16_t msInterval;
} Params;

typedef struct QueueNode
{
    void *value;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode* head;
    QueueNode* tail;
    pthread_mutex_t mutexId;
    pthread_cond_t condVar;
} Queue;

typedef struct {
    TMessage * tMessage;
    Queue * results;
} ThreadArgs;

typedef struct {
    Queue * messages;
    Queue * results;
    void *(*handler)(void *args);
} TaskArgs;

typedef struct {
    Queue * queueWaitTime;
    Queue * writeTime;
    Queue * readTime;
    Queue * algTime;
} ReportingArgs;

typedef struct {
    Queue *q;
    pthread_cond_t* condVar;
    pthread_mutex_t* mutex;
} IOArgs;