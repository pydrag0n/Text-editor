#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

int main(int argc, char **argv)
{
    if(argc > 2) {
        printf("usage: %s [file]", argv[0]);
        return 1;
    }
    if(initBuffer() == 0) {
        return 1;
    }
    if(argc == 2) {
        setFilename(argv[1]);
        read_file(getFilename(), 0);
    }
    return mainLoop();
}
