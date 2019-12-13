#include <iostream>
#include <fstream>
#include "message.pb.h"
#include "types.h"
#include "queue.h"

extern "C" void getMessages(Queue * messages);
extern "C" void addToQueueWrapper(Queue * messages, TMessage *m1);

using namespace std;
void getMessages(Queue * messages) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    uint8_t i = 0;
    while(true){
        TMessageProto message;
        ifstream input("hub", ios::in | ios::binary);
        message.ParseFromIstream(&input);
        std::cout << "Message type is "<< message.type() << std::endl;

        if(message.type()==3){
            std::cout << "FINISH" << std::endl;

            break;
        }
    }
        /*
        auto *m1 = (TMessage *)malloc(sizeof(TMessage));
        m1->Type = i%3;
        m1->Size = 1;
        m1->Data = (uint8_t *)1;

        addToQueueWrapper(messages, m1);

        i++;

        if(i > 30){
            auto *m1 = (TMessage *)malloc(sizeof(TMessage));
            m1->Type = 3;
            m1->Size = 1;
            m1->Data = (uint8_t *)1;
            addToQueueWrapper(messages, m1);
            break;
        }
    };
     */

}