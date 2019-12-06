#include "types.h"
#include "functions.h"
#include "reader.h"
#include <fstream>
#include <iostream>
#include "message.pb.h"
#include <list>
#include <pthread.h>
#include "perTaskHandler.h"

using namespace std;

void *reader(void* _args) {
    auto* args = (ReaderArgs *) _args;
    list<TMessage> messageQ;
    /*
    if (args->params->strategy == PER_THREAD)
        threadPerThreadHandler(&messageQ, args->resultArgs);
    else if (args->params->strategy == PER_TASK) {
        // threadPerTaskHandler(&messageQ, args->resultArgs);
    }
    else {
        std::cout<<"THREAD_POOL\n";
    }
    */
    getMessages(&messageQ);

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
    while(true){
        TMessage message;
        message.ParseFromIstream(&in);
        std::cout << message.type() << std::endl;
        if(message.type() == 3)
            break;
        // messageQ->push_front(message);
    };

    in.close();
}

void threadPerThreadHandler(std::list<TMessage> *messageQ, ResultArgs *resultArgs) {
    list<pthread_t> threadIds = {};

    while(true){
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
            break;
        }

        if(result != 0) {
            printf("No separate thread for u");
            return;
        }

        threadIds.push_front(taskHandlerId);
    }

    while(!threadIds.empty()) {
        pthread_join(threadIds.back(), nullptr);
        threadIds.pop_back();
    }
}
