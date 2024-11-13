#include <stdio.h>
#include <string.h>

#include "ed.h"

static char filename[255] = "";
static char *buffer = 0;

void setFilename(const char *const s)
{
    strncpy(filename, s, sizeof(filename));
    filename[sizeof(filename) - 1] = 0;
}
char* getFilename(void){ return filename; }

void setBuffer(char *const s)
{
    buffer = s;
}
char* getBuffer(void){ return buffer; }

void loop(void)
{
    char command[80];
    char status = ST_RUN_LOOP;
    while(status == ST_RUN_LOOP) {
        printf(DEFAULT_COMMAND_CHAR);
        fgets(command, 80, stdin);

        if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')) {
            command[strlen (command) - 1] = '\0';
        }

        status = parse(command);
    }
}
