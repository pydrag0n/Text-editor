#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

char parse(char *s, char **filename, char **buffer)
{
    char c = s[0];
    long size;
    switch(c) {
        case 'w':
            if(s[2] == 0) {
                size = writeFile(*filename, *buffer);
            } else {
                size = writeFile(&s[2], *buffer);
            }
            if(size != -1) {
                printf("write %ld\n", size);
            }
            break;
        case 'e':
            if(s[2] == 0) {
                size = readFile(*filename, buffer);
            } else {
                size = readFile(&s[2], buffer);
                if(*filename == 0){
                    *filename = calloc(1, strlen(&s[2]) + 1);
                }
                strcpy(*filename, &s[2]);
            }
            if(size != -1) {
                printf("read %ld\n", size);
            }
            break;
        case 'p':
            if (*buffer != 0) {
                printf("%s", *buffer);
            } else {
                printf("buffer empty\n");
            }
            break;
        case 'a':
            readConsole(buffer);
            break;
        case 'q':
            return ST_STOP_LOOP;
        default:
            printf("?\n");
    }
    return ST_RUN_LOOP;
}
