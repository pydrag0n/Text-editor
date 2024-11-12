#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

int main(int argc, char **argv)
{
    char *filename = 0;
    char *buffer = 0;

    if(argc > 2){
        printf("usage: %s [file]", argv[0]);
        return 1;
    }

    if(argc == 2){
        filename = malloc(strlen(argv[1]) + 1);
        strcpy(filename, argv[1]);
        long rsize = readFile(filename, &buffer);
        printf("read %ld\n", rsize);
    }

    char command[64];
    char status = 0;
    while(status == 0){
        fgets(command, 64, stdin);

        if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')){
            command[strlen (command) - 1] = '\0';
        }

        status = parse(command, filename, buffer);
    }

    if (buffer) {
        printf("buffer dump:\n%s\n", buffer);
    } else {
        printf("buffer empty\n");
    }
    free(buffer);
    return 0;
}
