#include <stdio.h>
#include <stdlib.h>

#include "ed.h"

int main()
{
    char *filename = "test.txt";

    char *buffer = 0;
    long rsize = readFile("read.txt", &buffer);
    long wsize = writeFile(filename, buffer);

    printf("read %ld\n", rsize);
    printf("write %ld\n", wsize);

    if (buffer) {
        printf("buffer dump:\n%s\n", buffer);
        free(buffer);
    }
    return 0;
}
