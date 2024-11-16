#include <stdio.h>
#include <stdlib.h>

#include "ed.h"

char execCommand(char *s)
{
    if(s[1] != ' ' && s[1] != '\0') {
        printf("?\n");
        return 0;
    }

    char c = s[0];
    switch(c) {
    case 'a':
        appendLines(&s, s[2] == 0 ? currentAddr() : atoi(&s[2]));
        break;
    case 'd':
        if(s[2] != 0) {
            deleteLines(atoi(&s[2]), atoi(&s[2]));
        } else {
            deleteLines(currentAddr(), currentAddr());
        }
        break;
    case 'e':
        if(modified()) {
            printf("warning: buffer modified. To force read use E\n");
            return 0;
        }
    case 'E':
        if(s[2] != 0) {
            setFilename(&s[2]);
        }
        read_file(getFilename(), 0);
        setModified(0);
        break;
    case 'p':
        displayLines(1, lastAddr());
        break;
    case 'q':
        if(modified()) {
            printf("warning: buffer modified. To force exit use Q\n");
            return 0;
        }
    case 'Q':
        return -1;
        break;
    case 'w':
        if(s[2] != 0) {
            setFilename(&s[2]);
        }
        write_file(getFilename(), 1);
        setModified(0);
        break;
    default:
        printf("?\n");
    }
    return 0;
}
