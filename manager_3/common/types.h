#pragma once
#include <stdint.h>
#include <pthread.h>
#include <bits/types/FILE.h>

typedef struct {
    uint8_t Type;
    uint64_t Size;
    uint8_t *Data;
} TMessage;

typedef struct {
    pthread_mutex_t *mutex;
    void *data;
} Data;

typedef struct {
    TMessage *message;
    struct timespec start;
} Message;

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
    Queue *q;
    pthread_cond_t* condVar;
    pthread_mutex_t* mutex;
    Data *counter;
    Data *queueStatistics;
} IOArgs;

typedef struct {
    TMessage * tMessage;
    IOArgs * writer;
    FILE *statistics;
} ThreadArgs;

typedef struct {
    struct timespec * startTime;
    uint16_t interval;
    Data *counter;
    FILE *reportFile;
} ReportArgs;