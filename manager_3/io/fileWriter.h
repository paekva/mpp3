#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

void writeToFileSingle(FILE* fin, pthread_mutex_t* mutex, long message);
void writeToFileMultiple(FILE* fin, pthread_mutex_t* mutex, int size, long *message);
long convertToMicroSeconds(struct timespec time);