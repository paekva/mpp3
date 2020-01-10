#include <iostream>
#include <fstream>
#include <pthread.h>
#include "message.pb.h"
#include "../common/types.h"
using namespace std;

extern "C" void getMessages(IOArgs *args);
extern "C" void addToQueueWrapper(Queue * messages, TMessage *m1);

void getMessages(IOArgs *args) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int counter = 0;
    FILE *readerStats = fopen("../readerStats.txt", "w");
    while(true){
        struct timespec startTime, endTime;
        long int duration;

        TMessageProto message;
        ifstream input("hub", ios::in | ios::binary);

        clock_gettime (CLOCK_REALTIME, &startTime);
        bool success = message.ParseFromIstream(&input);
        counter++;

        auto *m1 = (TMessage *)malloc(sizeof(TMessage));
        m1->Type = message.type();
        m1->Size = message.size();
        m1->Data = nullptr; //  message.data();

        addToQueueWrapper(args->q, m1);

        clock_gettime (CLOCK_REALTIME, &endTime);
        duration=1000000000*(endTime.tv_sec - startTime.tv_sec)+(endTime.tv_nsec - startTime.tv_nsec);
        fprintf(readerStats, "%ld\n", duration);

        if(message.type()==3){
            std::cout << "FINISH " << counter << std::endl;
            break;
        }
    }

}