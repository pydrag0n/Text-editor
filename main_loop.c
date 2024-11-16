#include <stdio.h>
#include <string.h>

#include "ed.h"

static char filename[255] = "";

void setFilename(char *const s)
{
    strncpy(filename, s, sizeof(filename));
    filename[sizeof(filename) - 1] = 0;
}
char* getFilename(void) { return filename; }

int mainLoop(void)
{
    char *cBuf = "";
    long len = 0;
    char status = 0;
    while(1) {
        printf("*");
        cBuf = getLine(&len);

        if ((strlen(cBuf) > 0) && (cBuf[strlen(cBuf) - 1] == '\n')) {
            cBuf[strlen(cBuf) - 1] = '\0';
        }

        status = execCommand(cBuf);
        if(status == 0) {continue;}
        if(status == -1) {return 0;}
    }
}
