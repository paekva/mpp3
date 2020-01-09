#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "common/types.h"

Params getOptions(int argc, char* argv[]){
    Strategy strategy = PER_THREAD;
    uint8_t threadsCount = 0;
    uint16_t msInterval = 800;

    while(1){
        const struct option long_options[] = {
                {"strategy", required_argument, NULL, 's'},
                {"count-threads", required_argument, NULL, 'c'},
                {NULL, 0, NULL,0}
        };

        int opt = getopt_long(argc,argv,"s:c:n:",long_options, NULL);
        if(opt != -1 && optarg != NULL) {
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

    Params args = {
            strategy,
            threadsCount,
            msInterval
    };

    return args;
}