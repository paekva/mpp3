#pragma once
#include <stdint.h>

typedef struct {
    uint8_t Type;
    uint64_t Size;
    uint8_t *Data;
} TMessage;