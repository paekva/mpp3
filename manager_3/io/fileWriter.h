#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

void writeToFileSingle(FILE* fin, pthread_mutex_t* mutex, uint8_t message);