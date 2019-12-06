#include "reader.h"
#include "parser.h"
#include "writer.h"

int main(int argc, char* argv[]) {
    pthread_t readerID, reporterID, writerID;
    std::list<std::string> results = {};
    pthread_mutex_t resultsMutex;
    pthread_mutex_init(&resultsMutex, nullptr);
    ResultArgs resultArgs = {
            &results,
            &resultsMutex,
            writerID
    };
    Params params = getOptions(argc, argv);

    ReaderArgs readerArgs = {
            &params,
            &resultArgs,
    };
    int readerResult = pthread_create(&readerID, nullptr, reader, &readerArgs);
    if(readerResult != 0){
        printf("No reader thread for u");
        return 1;
    }

    /*
    int writerResult = pthread_create(&writerID, nullptr, writer, &resultArgs);
    if(writerResult != 0) {
        printf("No writer thread for u");
        return 1;
    }
    */

    pthread_join(readerID, nullptr);

    // while(pthread_cancel(writerID) != 0);
    // pthread_join(writerID, nullptr);
    // pthread_join(reporterID, NULL);

    return 0;
}