#ifndef MANAGER_READER_H
#define MANAGER_READER_H

#include <list>
#include "types.h"
#include "message.pb.h"

void *reader(void* _args);
std::list<TProtoMessage> getMessages();
void threadPerThreadHandler(std::list<std::string> *results, pthread_mutex_t resultsMutex);

#endif //MANAGER_READER_H
