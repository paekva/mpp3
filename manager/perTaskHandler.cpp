#include "types.h"
#include "perTaskHandler.h"
#include "message.pb.h"
#include "functions.h"
#include <list>
#include <pthread.h>

void threadPerTaskHandler(std::list<TMessage> *messageQ, ResultArgs *resultArgs) {
    pthread_t fibbThreadId, powThreadId, sortThreadId;
    std::list<TMessage> * fibbQ, * powQ, * sortQ;
}