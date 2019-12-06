#include <stdio.h>
#include "protobufHandler.h"

int main() {
    char message;

    getMessages(&message);
    printf("%c Hello, World! \n", message);
    return 0;
}
