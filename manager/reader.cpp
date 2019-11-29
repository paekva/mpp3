#include "types.h"
#include "reader.h"
#include <fstream>
#include <iostream>
#include "message.pb.h"
#include <list>
#include <pthread.h>

using namespace std;

void *reader(void* _args) {
    auto* args = (ReaderArgs *) _args;
    list<string> results = {};
    pthread_mutex_t resultsMutex;
    pthread_mutex_init(&resultsMutex, NULL);

    if (args->strategy == PER_THREAD)
        threadPerThreadHandler(&results, resultsMutex);
    else if (args->strategy == PER_TASK)
        std::cout << "PER_TASK";
        // threadPerTaskHandler(messages, messagesCount);
    else {
        std::cout<<"THREAD_POOL\n";
    }

    return nullptr;
}

void *doNothing(void* _args)  {

}

list<TProtoMessage> getMessages() {
    list<TProtoMessage> receivedMessages = {};

    std::ifstream in("../messages.bin", std::ios_base::binary);

    TProtoMessages messages;
    messages.ParseFromIstream(&in);
    std::cout << "Hello, World!" <<  messages.item_size() << std::endl;

    for (int i = 0; i < messages.item_size(); i++) {
        const TProtoMessage &newMessage = messages.item(i);
        receivedMessages.push_front(newMessage);

        if (newMessage.type()) {
            std::cout << " \n " << newMessage.type();
        }
    }
    return receivedMessages;
}

void threadPerThreadHandler(std::list<std::string> *results, pthread_mutex_t resultsMutex) {
    cout << "Hey!";
    /*
     * pthread_t* taskHandlerIds = (pthread_t *)malloc(sizeof taskHandlerIds * messageCount);

    for(int i=0; i< messageCount; i++) {
        pthread_t taskHandlerId;
        taskHandlerIds[i] = taskHandlerId;
        TMessage message = messages[i];
        auto messageType = (EType) message.Type;
        int result = -1;

        if(messageType == FIBONACCI)
            result = pthread_create(&taskHandlerId, nullptr, doNothing, &message);
        else if(messageType == POW)
            result = pthread_create(&taskHandlerId, nullptr, doNothing, &message);
        else if(messageType == BUBBLE_SORT_UINT64)
            result = pthread_create(&taskHandlerId, nullptr, doNothing, &message);
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
     */
}
