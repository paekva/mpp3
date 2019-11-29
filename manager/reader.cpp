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
    list<TMessage> *messageQ = {};
    getMessages(messageQ);


    if (args->params->strategy == PER_THREAD)
        threadPerThreadHandler(messageQ, args->resultArgs);
    else if (args->params->strategy == PER_TASK)
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
    std::ifstream in("../../hub", std::ios_base::binary);
    TMessage message;

    do{
        message.ParseFromIstream(&in);
        std::cout << "Hello, World! " <<  message.type() << std::endl;
        messageQ->push_front(message);
    } while(message.type() != 3);

    in.close();
}

void threadPerThreadHandler(std::list<TMessage> *messageQ, ResultArgs *resultArgs) {
    // TODO: temporary not all messages are written
    TMessage tMessage = getNextMessage(messageQ);

    ThreadArgs threadArgs = {
            &tMessage,
            resultArgs
    };
    pthread_t taskHandlerId;
    int result = 0;

    if(tMessage.type() == FIBONACCI)
        result = pthread_create(&taskHandlerId, nullptr, fibbonachiThread, &threadArgs);
    else if(tMessage.type() == POW)
        result = pthread_create(&taskHandlerId, nullptr, powThread, &threadArgs);
    else if(tMessage.type() == BUBBLE_SORT_UINT64)
        result = pthread_create(&taskHandlerId, nullptr, bubbleSortThread, &threadArgs);
    else if(tMessage.type() == STOP) {
        while(pthread_cancel(resultArgs->writerThread) != 0){

        }
        return;
    }

    if(result != 0) {
        printf("No separate thread for u");
        return;
    }

    pthread_join(taskHandlerId, nullptr);
}
