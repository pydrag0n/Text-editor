#include <stdio.h>
#include <string.h>

#include "ed.h"

static char filename[255] = "";
static char color = 0;

void setFilename(char *const s)
{
    strncpy(filename, s, sizeof(filename));
    filename[sizeof(filename) - 1] = 0;
}
char* getFilename(void) { return filename; }

void switchColor(void) { color = !color; }

void cprint(char t)
{
    switch(t) {
        case COMMAND_CODE:
            if(color == 0) {
                printf(COMMAND_CHAR);
            } else {
                printf(COMMAND_CHAR_COLOR);
            }
            break;
        case ERROR_CODE_MEM:
            if(color == 0) {
                printf(ERROR_MSG_MEM);
            } else {
                printf(ERROR_MSG_MEM_COLOR);
            }
            break;
        case ERROR_CODE_FILENAME:
            if(color == 0) {
                printf(ERROR_MSG_FILENAME);
            } else {
                printf(ERROR_MSG_FILENAME_COLOR);
            }
            break;
        case ERROR_CODE_OPEN:
            if(color == 0) {
                printf(ERROR_MSG_OPEN);
            } else {
                printf(ERROR_MSG_OPEN_COLOR);
            }
            break;
    }
}

int mainLoop(void)
{
    char *cBuf = "";
    long len = 0;
    char status = 0;
    while(1) {
        cprint(COMMAND_CODE);
        cBuf = getLine(&len);

        if ((strlen(cBuf) > 0) && (cBuf[strlen(cBuf) - 1] == '\n')) {
            cBuf[strlen(cBuf) - 1] = '\0';
        }

        status = execCommand(cBuf);
        if(status == 0) {continue;}
        if(status == -1) {return 0;}
    }
}
