#include <stdlib.h>

#include "ed.h"

char resizeBuffer(char **const buf, long *const size, const long minSize)
{
    if(*size < minSize) {
        // change allocated size in 512 byte chunks to avoid excess syscalls
        const long newSize = (( minSize / 512 ) + 1) * 512;
        char *newBuf = 0;

        if(*buf) {
            newBuf = realloc(*buf, newSize);
        } else {
            newBuf = malloc(newSize);
        }

        if(newBuf == 0) {
            cprint(ERROR_CODE_MEM);
            return 0;
        }

        *size = newSize;
        *buf = newBuf;
    }
    return 1;
}
