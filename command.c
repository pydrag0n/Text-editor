#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

char parse(char *s)
{
    char *buffer = getBuffer();
    char c = s[0];
    long size;
    switch(c) {
        case WRITE_FILE_COMMAND:
            if(s[2] == 0) {
                size = writeFile();
            } else {
                setFilename(&s[2]);
                size = writeFile();
            }
            if(size != ST_ERROR) {
                printf("write %ld\n", size);
            }
            break;
        case READ_FILE_COMMAND:
            if(s[2] == 0) {
                size = readFile();
            } else {
                setFilename(&s[2]);
                size = readFile();
            }
            if(size != ST_ERROR) {
                printf("read %ld\n", size);
            }
            break;
        case PRINT_BUFFER_COMMAND:
            if(buffer != 0) {
                printf("%s", buffer);
            } else {
                printf("buffer empty\n");
            }
            break;
        case ENTER_INSERT_MODE:
            size = readConsole(ENTER_INSERT_MODE);
            if(size != ST_ERROR) {
                printf("saved to buffer %ld\n", size);
            }
            break;
        case ENTER_I_INSERT_MODE:
            size = readConsole(ENTER_I_INSERT_MODE);
            if(size != ST_ERROR) {
                printf("saved to buffer %ld\n", size);
            }
            break;
        case QUIT_COMMAND:
            return ST_STOP_LOOP;
        default:
            printf("?\n");
    }
    return ST_RUN_LOOP;
}
