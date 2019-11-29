#include "types.h"
#include "functions.h"
#include "reader.h"
#include <fstream>
#include <iostream>
#include "message.pb.h"
#include <list>
#include <pthread.h>

using namespace std;

void *reader(void* _args) {
    auto* args = (ReaderArgs *) _args;
    list<TMessage> messageQ = {};

    list<string> results = {};
    pthread_mutex_t resultsMutex;
    pthread_mutex_init(&resultsMutex, nullptr);

    if (args->strategy == PER_THREAD)
        threadPerThreadHandler(&messageQ, &results, resultsMutex);
    else if (args->strategy == PER_TASK)
        std::cout << "PER_TASK";
        // threadPerTaskHandler(messages, messagesCount);
    else {
        std::cout<<"THREAD_POOL\n";
    }

    return nullptr;
}

TMessage getNextMessage(list<TMessage> *messageQ){
    while(1){
        if(!messageQ->empty()){
            TMessage oldest = messageQ->back();
            messageQ->pop_back();
            return oldest;
        }
    };
}

void getMessages(list<TMessage> *messageQ) {
    std::ifstream in("../../message.bin", std::ios_base::binary);

    TMessage message;
    message.ParseFromIstream(&in);

    std::cout << "Hello, World! " <<  message.type() << std::endl;
    messageQ->push_front(message);

    in.close();
}

void threadPerThreadHandler(std::list<TMessage> *messageQ, std::list<std::string> *results, pthread_mutex_t resultsMutex) {
    // TODO: temporary not all messages are written
    getMessages(messageQ);
    TMessage tMessage = getNextMessage(messageQ);

    ThreadArgs threadArgs = {
            &tMessage,
            results,
            resultsMutex
    };
    pthread_t taskHandlerId;
    int result;

    if(tMessage.type() == FIBONACCI)
        result = pthread_create(&taskHandlerId, nullptr, fibbonachiThread, &threadArgs);
    else if(tMessage.type() == POW)
        result = pthread_create(&taskHandlerId, nullptr, powThread, &threadArgs);
    else if(tMessage.type() == BUBBLE_SORT_UINT64)
        result = pthread_create(&taskHandlerId, nullptr, bubbleSortThread, &threadArgs);
    else if(tMessage.type() == STOP) {
        return;
    }

    if(result != 0) {
        printf("No separate thread for u");
        return;
    }

    pthread_join(taskHandlerId, nullptr);
}
