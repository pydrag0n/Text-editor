#include <stdio.h>
#include <stdlib.h>

#include "ed.h"

long readFile(const char *filename, char **buffer)
{
    FILE *fp = fopen(filename, "r");
    if (fp == 0) {
        printf("Cannot open input file");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    *buffer = (char *)malloc(size + 1);
    if (*buffer == 0) {
        perror("Memory allocation error");
        fclose(fp);
        return -1;
    }

    fread(*buffer, 1, size, fp);
    (*buffer)[size] = '\0';

    fclose(fp);
    return size;
}

long writeFile(char *filename, char *buffer)
{
    FILE *fp = fopen(filename, "w");

    if(!fp){
        printf("Cannot open output file");
        return -1;
    }

    fputs(buffer, fp);
    // recalculation needed because printf count newline as one byte
    // but write to file as two bytes
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}