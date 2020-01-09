#include <iostream>
#include <fstream>
#include "message.pb.h"
#include "../common/types.h"
using namespace std;

extern "C" void getMessages(Queue * messages);
extern "C" void addToQueueWrapper(Queue * messages, TMessage *m1);

void getMessages(Queue * messages) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int counter = 0;
    FILE *readerStats = fopen("../readerStats.txt", "w");
    while(true){
        struct timespec mt1, mt2;
        long int tt;

        TMessageProto message;
        ifstream input("hub", ios::in | ios::binary);

        clock_gettime (CLOCK_REALTIME, &mt1);
        bool success = message.ParseFromIstream(&input);
        counter++;

        auto *m1 = (TMessage *)malloc(sizeof(TMessage));
        m1->Type = message.type();
        m1->Size = message.size();
        m1->Data = nullptr; //  message.data();
        addToQueueWrapper(messages, m1);

        clock_gettime (CLOCK_REALTIME, &mt2);
        tt=1000000000*(mt2.tv_sec - mt1.tv_sec)+(mt2.tv_nsec - mt1.tv_nsec);
        fprintf (readerStats, "%ld\n", tt);

        if(message.type()==3){
            std::cout << "FINISH " << counter << std::endl;
            break;
        }
    }

}