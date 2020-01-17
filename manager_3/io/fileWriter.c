#include <pthread.h>
#include <stdio.h>

long convertToMicroSeconds(struct timespec time) {
    return time.tv_sec * 1000000 + time.tv_nsec / 1000;
}

long convertToMicroSecondsWrapper(struct timespec time) {
    return convertToMicroSeconds(time);
}

void writeToFileSingle(FILE* fin, pthread_mutex_t* mutex, long message){
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_mutex_lock(mutex);
    fprintf(fin,"%ld\n", message);
    fflush(fin);
    pthread_mutex_unlock(mutex);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
}

void writeToFileMultiple(FILE* fin, pthread_mutex_t* mutex, int size, long *message){
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_mutex_lock(mutex);
    for(int j =0;j<size; j++){
        fprintf(fin,"%ld ", message[j]);
    }
    fprintf(fin,"\n");
    fflush(fin);
    pthread_mutex_unlock(mutex);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
}