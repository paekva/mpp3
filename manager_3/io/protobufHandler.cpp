#include <iostream>
#include <fstream>
#include <pthread.h>
#include "message.pb.h"
#include "../common/types.h"
using namespace std;

extern "C" void getMessages(IOArgs *args);
extern "C" void addToQueueWrapper(Queue * messages, TMessage *m1);

void incrementCounter(int *counter, pthread_mutex_t* mutex){
    pthread_mutex_lock(mutex);
    *counter = *counter + 1;
    pthread_mutex_unlock(mutex);
}

void getMessages(IOArgs *args) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::ofstream readerInfo;
    readerInfo.open("./manager_3/results/reader.txt");
    if(!readerInfo.is_open()){
        cout << strerror(errno) << endl;
    }

    while(true){
        struct timespec startTime, endTime;
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

        addToQueueWrapper(args->q, m1);
        incrementCounter(args->counter, args->counterMutex);

        pthread_mutex_lock(args->mutex);
        pthread_cond_signal(args->condVar);
        pthread_mutex_unlock(args->mutex);

        clock_gettime (CLOCK_REALTIME, &endTime);
        duration=1000000*(endTime.tv_sec - startTime.tv_sec)+(endTime.tv_nsec - startTime.tv_nsec)/1000;

        if (readerInfo.is_open())
        {
            readerInfo << duration << endl;
        }

        if(message.type()==3)
            break;
    }

    if (readerInfo.is_open()) readerInfo.close();
}