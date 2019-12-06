#include <iostream>
#include "message.pb.h"
#include "types.h"
#include "queue.h"

extern "C" void getMessages(Queue * messages);
extern "C" void addToQueueWrapper(Queue * messages, TMessage *m1);

void getMessages(Queue * messages) {
    std::istream *ins = &std::cin;

    uint8_t i = 0;
    while(true){
        // TMessageProto message;
        // message.ParseFromIstream(ins);
        // std::cout << message.type() << std::endl;

        auto *m1 = (TMessage *)malloc(sizeof(TMessage));
        m1->Type = i;
        m1->Size = 1;
        m1->Data = (uint8_t *)1;

        addToQueueWrapper(messages, m1);

        i++;

        if(i==4)
            break;
    };

}