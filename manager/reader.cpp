#include "types.h"
#include <fstream>
#include <iostream>
#include "message.pb.h"


TMessage *getMessages() {
    std::ifstream in("../messages.bin", std::ios_base::binary);

    TMessages messages;
    messages.ParseFromIstream(&in);
    std::cout << "Hello, World!" <<  messages.item_size() << std::endl;

    for (int i = 0; i < messages.item_size(); i++) {
        const TMessage &mess = messages.item(i);
        if (mess.type()) {
            std::cout << " \n " << mess.type();
        }
    }
}

void *reader(void* _args) {
    TMessage *messages = getMessages();

    /*
    auto* args = (ReaderArgs *) _args;

    if (args->strategy == PER_THREAD)
        std::cout << "PER_TASK";
        // threadPerThreadHandler(messages, messagesCount);
    else if (args->strategy == PER_TASK)
        std::cout << "PER_TASK";
        // threadPerTaskHandler(messages, messagesCount);
    else {
        std::cout<<"THREAD_POOL\n";
    }
     */

    return nullptr;
}

/*
void threadPerThreadHandler(TMessage messages[], int messageCount) {
    pthread_t* taskHandlerIds = (pthread_t *)malloc(sizeof taskHandlerIds * messageCount);

    for(int i=0; i< messageCount; i++) {
        pthread_t taskHandlerId;
        taskHandlerIds[i] = taskHandlerId;
        TMessage message = messages[i];
        auto messageType = (EType) message.Type;
        int result = -1;

        if(messageType == FIBONACCI)
            result = pthread_create(&taskHandlerId, nullptr, fibbonachiThread, &message);
        else if(messageType == POW)
            result = pthread_create(&taskHandlerId, nullptr, powThread, &message);
        else if(messageType == BUBBLE_SORT_UINT64)
            result = pthread_create(&taskHandlerId, nullptr, bubbleSortThread, &message);
        else if(messageType == STOP) {
        }

        if(result != 0){
            printf("No separate thread for u");
            return;
        }
    }

    for(int i=0; i< messageCount; i++) {
        pthread_join(taskHandlerIds[i], nullptr);
    }

    free(taskHandlerIds);
}
*/