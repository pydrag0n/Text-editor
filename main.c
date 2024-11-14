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

    if(argc == 2) {
        setFilename(argv[1]);
        long size = readFile();
        if(size != -1) {
            printf("read %ld\n", size);
        }
    }

    return mainLoop();
}
