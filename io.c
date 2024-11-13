#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

long readFile(const char *filename, char **buffer)
{
    if(filename == 0) {
        printf("No current filename\n");
        return ST_ERROR;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == 0) {
        printf("Cannot open input file\n");
        return ST_ERROR;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    *buffer = realloc(*buffer, size + 1);
    if (*buffer == 0) {
        perror("Memory allocation error\n");
        fclose(fp);
        return ST_ERROR;
    }

    fread(*buffer, 1, size, fp);

    fclose(fp);
    return size;
}

long writeFile(char *filename, char *buffer)
{
    if(filename == 0) {
        printf("No current filename\n");
        return ST_ERROR;
    }

    FILE *fp = fopen(filename, "w");
    if(!fp) {
        printf("Cannot open output file\n");
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

short readConsole(char **buffer)
{
    char text[256];
    int line = 1;
    long totalSize = 0;

    *buffer = (char *)calloc(1, 1);

    if (*buffer == 0) {
        perror("Memory allocation error\n");
        return ST_ERROR;
    }

    while (1) {
        printf("%i ", line);
        fgets(text, sizeof(text), stdin);

        if (text[0] == '.' && text[1] == '\n') {
            break;
        }

        int textLength = strlen(text);

        char *newBuffer = realloc(*buffer, totalSize + textLength + 1);
        if (newBuffer == NULL) {
            perror("Memory allocation error\n");
            free(*buffer);
            return ST_ERROR;
        }

        *buffer = newBuffer;

        strcpy(*buffer + totalSize, text);
        totalSize += textLength;
        line += 1;
    }
    return 0;
}
