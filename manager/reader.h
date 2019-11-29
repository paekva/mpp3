#ifndef MANAGER_READER_H
#define MANAGER_READER_H

#include <list>
#include "types.h"
#include "message.pb.h"

void *reader(void* _args);
void getMessages(std::list<TMessage> *messageQ);
TMessage getNextMessage(std::list<TMessage> *messageQ);
void threadPerThreadHandler(std::list<TMessage> *messageQ, std::list<std::string> *results, pthread_mutex_t resultsMutex);

#endif //MANAGER_READER_H