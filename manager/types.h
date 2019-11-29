#ifndef TASKMANAGER_TYPES_H
#define TASKMANAGER_TYPES_H
#include <cstdint>

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

typedef struct
{
    Strategy strategy;
    uint8_t threadsCount;
    uint16_t msInterval;
} ReaderArgs;

typedef struct {

} WriterArgs;

#endif //TASKMANAGER_TYPES_H