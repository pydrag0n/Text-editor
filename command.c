#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

char execCommand(char *s)
{
    if(s[1] != '\n' && s[1] != ' ' && s[1] != '\0') {
        printf("?\n");
        return 0;
    }

    char c = s[0];
    switch(c) {
        case 'C':
            switchColor();
            break;
        case 'a':
            appendLines(&s, s[2] == 0 ? currentAddr() : atoi(&s[2]));
            break;
        case 'p':
            displayLines(1, lastAddr());
            break;
        case 'e':
            if(s[2] != 0) {
                setFilename(&s[2]);
            }
            read_file(getFilename(), 0);
            setModified(0);
            break;
        case 'w':
            if(s[2] != 0) {
                setFilename(&s[2]);
            }
            write_file(getFilename(), 1);
            setModified(0);
            break;
        case 'q':
            return -1;
        default:
            printf("?\n");
    }
    return 0;
}
