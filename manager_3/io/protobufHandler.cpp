#include <iostream>
#include <fstream>
#include <pthread.h>
#include "message.pb.h"
#include "../common/types.h"

using namespace std;

extern "C" void getMessages(IOArgs *args);
extern "C" void addToQueueWrapper(Queue * messages, void *message);
extern "C" long convertToMicroSecondsWrapper(struct timespec time);

void incrementCounter(void *_counter, pthread_mutex_t* mutex){
    int *counter = (int *)_counter;
    pthread_mutex_lock(mutex);
    *counter = *counter + 1;
    pthread_mutex_unlock(mutex);
}

void getMessages(IOArgs *args) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::ofstream readerInfo;
    readerInfo.open("./manager_3/results/reader.txt");

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    while(true){
        struct timespec startTime, endTime, queueStartTime;
        long int duration;

        TMessageProto message;
        ifstream input("hub", ios::in | ios::binary);

        clock_gettime (CLOCK_REALTIME, &startTime);
        bool success = message.ParseFromIstream(&input);
        if(!success) {
            continue;
        }

        auto *m1 = (TMessage *)malloc(sizeof(TMessage));
        m1->Type = message.type();
        m1->Size = message.size();

        int count = message.data().size();
        auto *array = new uint8_t[count];

        for(int i=0;i<count;i++){
            array[i] = message.data(i);
        }

        m1->Data = array;

        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);

        auto *newMessage = (Message *)malloc(sizeof(Message));
        newMessage->message = m1;
        clock_gettime (CLOCK_REALTIME, &queueStartTime);
        newMessage->start = queueStartTime;

        addToQueueWrapper(args->q, newMessage);
        incrementCounter(args->counter->data, args->counter->mutex);

        pthread_mutex_lock(args->mutex);
        pthread_cond_signal(args->condVar);
        pthread_mutex_unlock(args->mutex);

        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);

        clock_gettime (CLOCK_REALTIME, &endTime);
        duration = convertToMicroSecondsWrapper(endTime) - convertToMicroSecondsWrapper(startTime);

        if (readerInfo.is_open())
        {
            readerInfo << duration << endl;
        }

        if(message.type()==3)
            break;
    }

    if (readerInfo.is_open()) readerInfo.close();
}