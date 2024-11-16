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
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == 0) {
        cprint(ERROR_CODE_OPEN);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    free(buffer);
    buffer = calloc(1, size + 1);
    if (buffer == 0) {
        cprint(ERROR_CODE_MEM);
        fclose(fp);
        return -1;
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
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if(fp == 0) {
        cprint(ERROR_CODE_OPEN);
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

long readConsole(char _Mode) // a or i
{
    char *buffer = getBuffer();
    char *bufferTop = getBufferTop();
    char text[256] = "";
    if(buffer == 0) {_Mode = 'i';}

    static long line = 1;
    long totalSize = 0;
    if(_Mode == 'i') {
        line = 1;
    } else {
        totalSize = bufferTop - buffer;
    }

    while (1) {
        printf("%ld ", line);
        fgets(text, sizeof(text), stdin);

        if (text[0] == COMMAND_QUIT_INSERT && text[1] == '\n') {
            break;
        }

        long textLength = strlen(text);

        if(buffer == 0) {
            buffer = calloc(1, sizeof(text));
        }
        char *newBuffer = realloc(buffer, totalSize + textLength + 1);
        if (newBuffer == 0) {
            cprint(ERROR_CODE_MEM);
            free(buffer);
            return -1;
        }

        buffer = newBuffer;
        setBuffer(buffer);

        bufferTop = buffer + totalSize;
        strcpy(bufferTop, text);

        totalSize += textLength;
        bufferTop += textLength;
        setBufferTop(bufferTop);

        line++;
    }
    return totalSize;
}

void printBuffer(void)
{
    char *buffer = getBuffer();
    long line = 1;
    char *p = 0;
    while(*buffer != '\0') {
        p = strchr(buffer, '\n') + 1;
        printf("%ld ", line);
        printf("%.*s", (int)(p - buffer), buffer);
        buffer = p;
        line++;
    }
}

// print a range of lines to stdout
char displayLines(long from, const long to)
{
    line_t *ep = searchLineNode(to+1);
    line_t *bp = searchLineNode(from);
    long line = from;

    while(bp != ep) {
        const char *const s = getSbufLine(bp);
        if(!s) {
            return 0;
        }
        setCurrentAddr(from++);
        printf("%ld ", line);
        printf("%s\n",s);
        bp = bp->forw;
        line++;
    }
    return 1;
}

char* getLine(long *const sizep)
{
    static char *buf = 0;
    static long bufsz = 0;
    long i = 0;

    while(1) {
        short c = getchar();

        if(resizeBuffer(&buf, &bufsz, i + 2) == 0) {
            if(sizep) {
                *sizep = 0;
                return 0;
            }
        }

        buf[i++] = c;
        if(c != '\n') {continue;}

        buf[i] = 0;
        if(sizep) {*sizep = i;}
        return buf;
    }
}

// Read a line of text from a stream.
// Return pointer to buffer and line size
char *read_stream_line(FILE *const fp, long *const sizep)
{
    static char *buf = 0;
    static long bufsz = 0;
    short c = 0;
    long i = 0;

    while(1) {
        if(resizeBuffer(&buf, &bufsz, i + 2) == 0) {
            return 0;
        }
        c = getc(fp);
        if(c == EOF) {
            break;
        }
        buf[i++] = c;
        if(c == '\n') {
            break;
        }
    }
    buf[i] = 0;
    if(c == EOF && i != 0) {
        buf[i] = '\n';
        buf[i+1] = 0;
        i++;
    }
    *sizep = i;
    return buf;
}

// read a stream into the editor buffer; return total size of data read
long read_stream(FILE *const fp, const long addr)
{
    line_t *lp = searchLineNode(addr);
    long total_size = 0;

    setCurrentAddr(addr);
    while(1) {
        long size = 0;
        char *const s = read_stream_line(fp, &size);
        if(s == 0) {
            return -1;
        }
        if(size > 0) {
            total_size += size;
        } else {
            break;
        }
        if(putSbufLine(s, size, currentAddr()) == 0) {
            return -1;
        }
        lp = lp->forw;
    }
    return total_size;
}

// read a named file/pipe into the buffer; return line count
long read_file(char *const filename, const long addr)
{
    FILE *fp = fopen(filename, "r");
    if(fp == 0) {
        printf("Cannot open input file\n");
        return -1;
    }
    long size = read_stream(fp, addr);
    if(size < 0) {
        return -1;
    }
    if(fclose(fp) != 0) {
        printf("Cannot close input file\n");
        return -1;
    }
    printf("%ld\n", size);
    return currentAddr() - addr;
}

// write a range of lines to a stream
long write_stream(FILE *const fp, long from)
{
    long to = lastAddr();
    line_t *lp = searchLineNode(from);
    long size = 0;

    while(from <= to) {
        char *p = getSbufLine(lp);
        if(p == 0) {
            return -1;
        }
        long len = lp->len;
        p[len++] = '\n';
        size += len;
        while(--len >= 0) {
            if(fputc(*p++, fp) == EOF) {
                printf("Cannot write file\n");
                return -1;
            }
        }
        ++from;
        lp = lp->forw;
    }
    return size;
}


// write a range of lines to a named file/pipe; return line count
long write_file(const char *const filename, const long from)
{
    FILE *fp = fopen(filename, "w");
    if(fp == 0) {
        printf("Cannot open output file\n");
        return -1;
    }
    long size = write_stream(fp, from);
    if(size < 0) {
        return -1;
    }
    if(fclose(fp) != 0) {
        printf("Cannot close output file\n");
        return -1;
    }
    printf("%ld\n", size);
    return lastAddr() - from + 1;
}
