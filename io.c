#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

long readFile(void)
{
    const char *filename = getFilename();
    char *buffer = getBuffer();

    if(filename == 0) {
        cprint(ERROR_CODE_FILENAME);
        return ST_ERROR;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == 0) {
        cprint(ERROR_CODE_OPEN);
        return ST_ERROR;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    free(buffer);
    buffer = calloc(1, size + 1);
    if (buffer == 0) {
        cprint(ERROR_CODE_MEM);
        fclose(fp);
        return ST_ERROR;
    }
    setBuffer(buffer);

    fread(buffer, 1, size, fp);

    fclose(fp);
    return size;
}

long writeFile(void)
{
    const char *filename = getFilename();
    const char *buffer = getBuffer();

    if(filename == 0) {
        cprint(ERROR_CODE_FILENAME);
        return ST_ERROR;
    }

    FILE *fp = fopen(filename, "w");
    if(fp == 0) {
        cprint(ERROR_CODE_OPEN);
        return ST_ERROR;
    }

    fputs(buffer, fp);
    // recalculation needed because printf count newline as one byte
    // but write to file as two bytes
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

long readConsole(char _Mode) // a or i
{
    char *buffer = getBuffer();
    char *bufferTop = getBufferTop();
    if(buffer == 0) {_Mode = 'i';}

    char text[256] = "";
    int line = 1;
    long totalSize = bufferTop - buffer;

    while (1) {
        printf("%i ", line);
        fgets(text, sizeof(text), stdin);

        if (text[0] == QUIT_INSERT_MODE_COMMAND && text[1] == '\n') {
            break;
        }

        int textLength = strlen(text);

        if(buffer == 0) {
            buffer = calloc(1, sizeof(text));
        }
        char *newBuffer = realloc(buffer, totalSize + textLength + 1);
        if (newBuffer == 0) {
            cprint(ERROR_CODE_MEM);
            free(buffer);
            return ST_ERROR;
        }

        buffer = newBuffer;
        setBuffer(newBuffer);

        if(_Mode == 'i'){
            strcpy(buffer + totalSize, text);
        } else {
            strcpy(bufferTop, text);
        }

        bufferTop = newBuffer + totalSize + textLength;
        setBufferTop(newBuffer + totalSize + textLength);

        totalSize += textLength;
        line += 1;
    }
    return totalSize;
}
