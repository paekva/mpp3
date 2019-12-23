#include <iostream>
#include <fstream>
#include "message.pb.h"
#include "types.h"

extern "C" void getMessages(Queue * messages);
extern "C" void addToQueueWrapper(Queue * messages, TMessage *m1);

using namespace std;
void getMessages(Queue * messages) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int counter = 0;
    while(true){
        TMessageProto message;
        ifstream input("hub", ios::in | ios::binary);
        message.ParseFromIstream(&input);
        counter++;

        auto *m1 = (TMessage *)malloc(sizeof(TMessage));
        m1->Type = message.type();
        m1->Size = message.size();
        m1->Data = nullptr; //  message.data();
        addToQueueWrapper(messages, m1);

        if(message.type()==3){
            std::cout << "FINISH " << counter << std::endl;

            break;
        }
    }

}