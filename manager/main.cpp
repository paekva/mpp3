#include "reader.h"
#include "parser.h"

int main(int argc, char* argv[]) {

    ReaderArgs args = getOptions(argc, argv);

    pthread_t readerID, reporterID;

    int readerResult = pthread_create(&readerID, nullptr, reader, &args);
    if(readerResult != 0){
        printf("No reader thread for u");
        return 1;
    }

    pthread_join(readerID, nullptr);
    // pthread_cancel(reporterID);
    // pthread_join(reporterID, NULL);

    return 0;
}