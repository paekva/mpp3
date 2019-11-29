#include <getopt.h>
#include <cstdlib>
#include <cstring>
#include "types.h"

ReaderArgs getOptions(int argc, char* argv[]){
    Strategy strategy = PER_THREAD;
    uint8_t threadsCount = 0;
    uint16_t msInterval = 800;

    while(true){
        const struct option long_options[] = {
                {"strategy", required_argument, nullptr, 's'},
                {"count-threads", required_argument, nullptr, 'c'},
                {nullptr,0,nullptr,0}
        };

        int opt = getopt_long(argc,argv,"s:c:n:",long_options, nullptr);
        if(opt != -1 && optarg != nullptr) {
            switch (opt) {
                case 's':{
                    if(strcmp(optarg,"per_task") == 0)
                        strategy = PER_TASK;
                    else if(strcmp(optarg, "per_thread") == 0)
                        strategy = PER_THREAD;
                    else
                        strategy = THREAD_POOL;
                    break;
                }
                case 'c': {
                    threadsCount = atoi(optarg);
                    break;
                }
                case 'n': {
                    msInterval = atoi(optarg);
                    break;
                }
                default:
                    break;
            }
        } else break;
    }

    ReaderArgs args = {
            strategy,
            threadsCount,
            msInterval
    };

    return args;
}