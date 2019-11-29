#include "writer.h"
#include "types.h"

void *writer(void* _args) {
    auto *args = (ResultArgs *)_args;

    while(args->results->empty()){
        if(!args->results->empty()){
            std::cout << "Result is : " << args->results->back();
            args->results->pop_back();
            break;
        }
    }
    return nullptr;
}