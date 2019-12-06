#include "writer.h"
#include "types.h"
#include <pthread.h>

void *writer(void* _args) {
    auto *args = (ResultArgs *)_args;

    while(true){
        if(!args->results->empty()){
            pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);

            pthread_mutex_lock(args->resultsMutex);
            std::cout << "Result is : " << args->results->back();
            args->results->pop_back();
            pthread_mutex_unlock(args->resultsMutex);
        } else {
            pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
        }
    }
}