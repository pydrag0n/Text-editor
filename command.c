#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

char execCommand(char *s)
{
    char *buffer = getBuffer();
    char c = s[0];

    if(s[1] != '\n' && s[1] != ' ' && s[1] != '\0') {
        printf("?\n");
        return 0;
    }

    long size;
    switch(c) {
        case COMMAND_WRITE_FILE:
            if(s[2] == 0) {
                size = writeFile();
            } else {
                setFilename(&s[2]);
                size = writeFile();
            }
            if(size != -1) {
                printf("write %ld\n", size);
            }
            break;
        case COMMAND_READ_FILE:
            if(s[2] == 0) {
                size = readFile();
            } else {
                setFilename(&s[2]);
                size = readFile();
            }
            if(size != -1) {
                printf("read %ld\n", size);
            }
            break;
        case COMMAND_PRINT_BUFFER:
            if(buffer != 0) {
                printBuffer();
            } else {
                printf("buffer empty\n");
            }
            break;
        case COMMAND_APPEND:
            size = readConsole(COMMAND_APPEND);
            if(size != -1) {
                printf("saved to buffer %ld\n", size);
            }
            break;
        case COMMAND_INSERT:
            size = readConsole(COMMAND_INSERT);
            if(size != -1) {
                printf("saved to buffer %ld\n", size);
            }
            break;
        case COMMAND_COLOR:
            switchColor();
            break;
        case 'A':
            appendLines(&s, currentAddr());
            break;
        case COMMAND_QUIT:
            return QUIT;
        default:
            printf("?\n");
    }
    return 0;
}
