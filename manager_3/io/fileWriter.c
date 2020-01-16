#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

long convertToMicroSeconds(struct timespec time) {
    return time.tv_sec * 1000000 + time.tv_nsec / 1000;
}

void writeToFileSingle(FILE* fin, pthread_mutex_t* mutex, long message){
    pthread_mutex_lock(mutex);
    fprintf(fin,"%ld\n", message);
    fflush(fin);
    pthread_mutex_unlock(mutex);
}

void writeToFileMultiple(FILE* fin, pthread_mutex_t* mutex, int size, long *message){
    pthread_mutex_lock(mutex);
    for(int j =0;j<size; j++){
        fprintf(fin,"%ld ", message[j]);
    }
    fprintf(fin,"\n");
    fflush(fin);
    pthread_mutex_unlock(mutex);
}