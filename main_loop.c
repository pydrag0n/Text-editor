#include <stdio.h>
#include <string.h>

#include "ed.h"

static char filename[255] = "";
static char *buffer = 0;
static char *bufferTop = 0;
static char color = 0;

void setFilename(char *const s)
{
    strncpy(filename, s, sizeof(filename));
    filename[sizeof(filename) - 1] = 0;
}
char* getFilename(void) { return filename; }

void setBuffer(char *const s) { buffer = s; }
char* getBuffer(void) { return buffer; }

void setBufferTop(char *const s) { bufferTop = s; }
char* getBufferTop(void) { return bufferTop; }

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

void loop(void)
{
    char command[80];
    char status = ST_RUN_LOOP;
    while(status == ST_RUN_LOOP) {
        cprint(COMMAND_CODE);
        fgets(command, 80, stdin);

        if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')) {
            command[strlen (command) - 1] = '\0';
        }

        status = parse(command);
    }
}
