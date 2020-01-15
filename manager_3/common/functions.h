#include <unistd.h>

void *fibbonachiTask(void * _args);
void *powTask(void * _args);
void *bubbleSortTask(void * _args);

__uint8_t powMethod(__uint8_t base, __uint8_t power);
__uint8_t fibbonacci(__uint8_t number);
__uint8_t* bubbleSort(__uint8_t* array, int arrayLength);