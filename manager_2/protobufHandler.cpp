#include <iostream>
#include "message.pb.h"

extern "C" void getMessages(char *message);

void getMessages(char * message) {
    //std::istream *ins = &std::cin;

    while(true){
        // ins->readsome(message, 10);
        *message = 'c';
        break;
        // TMessage message;
        // message.ParseFromIstream(ins);
        // std::cout << message.type() << std::endl;
        // if(message.type() == 3)
        //    break;
    };

}