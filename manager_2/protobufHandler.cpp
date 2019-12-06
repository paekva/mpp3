#include <iostream>
#include "message.pb.h"
#include "types.h"
#include "queue.h"

extern "C" void getMessages(Queue * messages);
extern "C" void addToQueueWrapper(Queue * messages, TMessage *m1);

void getMessages(Queue * messages) {
    //std::istream *ins = &std::cin;

    while(true){
        // ins->readsome(message, 10);

        TMessage m1 = {
                1,
                1,
                (uint8_t *)1
        };
        addToQueueWrapper(messages, &m1);
        addToQueueWrapper(messages, &m1);
        addToQueueWrapper(messages, &m1);

        break;
        // TMessage message;
        // message.ParseFromIstream(ins);
        // std::cout << message.type() << std::endl;
        // if(message.type() == 3)
        //    break;
    };

}