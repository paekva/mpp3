#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

void writeToFileSingle(FILE* fin, pthread_mutex_t* mutex, uint8_t message);
void writeToFileMultiple(FILE* fin, pthread_mutex_t* mutex, int size, uint8_t *message);