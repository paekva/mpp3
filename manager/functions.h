//
// Created by paekva on 29.11.2019.
//

#ifndef MANAGER_FUNCTIONS_H
#define MANAGER_FUNCTIONS_H
#include "types.h"

void *fibbonachiThread(void * args);
void *powThread(void * args);
void *bubbleSortThread(void * args);
void addResult(ResultArgs *resultArgs);
#endif //MANAGER_FUNCTIONS_H
