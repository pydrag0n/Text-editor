#include <stdio.h>

#include "ed.h"

char parse(char *s, char *filename, char *buffer)
{
    char c = s[0];
    switch(c){
        case 'w':
            long size;
            if(s[2] == 0){
                size = writeFile(filename, buffer);
            } else {
                size = writeFile(&s[2], buffer);
            }
            printf("write %ld\n", size);
            break;
        case 'p':
            if (buffer) {
                printf("buffer dump:\n%s\n", buffer);
            } else {
                printf("buffer empty\n");
            }
            break;
        case 'q':
            return 1;
        default:
            printf("?\n");
    }
    return 0;
}
