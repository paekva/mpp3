#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

void writeToFileSingle(FILE* fin, pthread_mutex_t* mutex, long message){
    pthread_mutex_lock(mutex);
    fprintf(fin,"%ld\n", message);
    fflush(fin);
    pthread_mutex_unlock(mutex);
}

void writeToFileMultiple(FILE* fin, pthread_mutex_t* mutex, int size, uint8_t *message){
    pthread_mutex_lock(mutex);
    for(int j =0;j<size; j++){
        fprintf(fin,"%hhu ", message[j]);
    }
    fprintf(fin,"\n");
    fflush(fin);
    pthread_mutex_unlock(mutex);
}