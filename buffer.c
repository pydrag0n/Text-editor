#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ed.h"

static long current_addr_ = 0; // current line address in buffer
static long last_addr_ = 0;    // last(head) line address in buffer
static char modified_ = 0;     // if buffer was modified since last read/write

static char seek_write = 0;	   // seek before writing
static FILE *sfp = 0;		   // scratch file pointer
static long sfpos = 0;		   // scratch file position

static line_t buffer_head;     // linked list of line_t

long currentAddr(void) { return current_addr_; }
long incCurrentAddr(void)
{
    if( ++current_addr_ > last_addr_ ) {
        current_addr_ = last_addr_;
    }
    return current_addr_;
}
void setCurrentAddr(const long addr) { current_addr_ = addr; }

long lastAddr(void) { return last_addr_; }

char modified(void) { return modified_; }
void setModified(const char m) { modified_ = m; }

long incAddr(long addr)
{
    if(++addr > last_addr_) {
        addr = 0;
    }
    return addr;
}

long decAddr(long addr)
{
    if(--addr < 0) {
        addr = last_addr_;
    }
    return addr;
}

// link two nodes
void linkNodes(line_t *const prev, line_t *const next)
{
    prev->forw = next;
    next->back = prev;
}

// insert new node between prev and prev->forw
void insertNode(line_t *const lp, line_t *const prev)
{
    linkNodes(lp, prev->forw);
    linkNodes(prev, lp);
}

// open scratch file
char openSbuf(void)
{
    sfp = tmpfile();
    if(!sfp) {
        printf("Cannot open temp file\n");
        return 0;
    }
    return 1;
}

// close scratch file
char closeSbuf(void)
{
    if(sfp) {
        if(fclose(sfp) != 0 ) {
            printf("Cannot close temp file\n");
            return 0;
        }
        sfp = 0;
    }
    sfpos = 0;
    seek_write = 0;
    return 1;
}

// init linked list and scratch file
char initBuffer(void)
{
    if(openSbuf() == 0) {return 0;}
    linkNodes(&buffer_head, &buffer_head);
    return 1;
}

// return a pointer to a copy of a line node, or to a new node if lp == 0
line_t *dupLineNode(line_t *const lp)
{
    line_t *const p = (line_t*)malloc(sizeof(line_t));
    if(p == 0) {
        cprint(ERROR_CODE_MEM);
        return 0;
    }

    if(lp) {
        p->pos = lp->pos;
        p->len = lp->len;
    }

    return p;
}

// return pointer to a line node in the editor buffer
line_t *searchLineNode(const long addr)
{
    line_t *lp = &buffer_head;
    long o_addr = 0;

    while(o_addr < addr) {
        ++o_addr;
        lp = lp->forw;
    }
    return lp;
}

// add a line node in the editor buffer after the given line
void addLineNode(line_t *const lp, const long addr)
{
    line_t *const prev = searchLineNode(addr);
    insertNode(lp, prev);
    ++last_addr_;
}

// write a line of text to the scratch file and add a line node to the
// editor buffer; return a pointer to the end of the text
char *putSbufLine(char *const buf, const long size, const long addr)
{
    // create empty line
    line_t *const lp = dupLineNode(0);
    // search for line end in buffer
    char *const p = (char*)memchr(buf, '\n', size);

    if(lp == 0) {
        return 0;
    }
    if(p == 0) {
        printf("Line too long\n");
        return 0;
    }
    long len = p - buf;
    // move file pointer to end if it was changed
    if(seek_write) {
        if(fseek(sfp, 0, SEEK_END) != 0) {
            printf("Cannot seek temp file\n");
            return 0;
        }
        sfpos = ftell(sfp);
        seek_write = 0;
    }
    if((long)fwrite(buf, 1, len, sfp) != len) {
        sfpos = -1;
        printf("Cannot write temp file\n");
        return 0;
    }
    lp->pos = sfpos;
    lp->len = len;
    addLineNode(lp, addr);
    ++current_addr_;
    sfpos += len;
    return p + 1;
}

// Insert text from stdin to after line n;
// stop when a single period is read.
// Return false if insertion fails
char appendLines(char **bufp, const long addr)
{
    long size = 0;
    current_addr_ = addr;

    while(1) {
        *bufp = getLine(&size);
        if(*bufp == 0) {
            return 0;
        }
        if(size == 2 && **bufp == '.') {
            *bufp += size;
            return 1;
        }
        if(putSbufLine(*bufp, size, current_addr_) == 0) {
            return 0;
        }
        *bufp += size;
        modified_ = 1;
    }
}

// print a range of lines to stdout
char displayLines(const long from, const long to)
{
    line_t *ep = searchLineNode(to+1);
    line_t *bp = searchLineNode(from);
    static char *buf = 0;
    static long bufsz = 0;
    long line = from;
    seek_write = 1;

    while(bp != ep) {
        long len = bp->len;
        if(fseek(sfp, bp->pos, SEEK_SET) != 0) {
            printf("Cannot seek temp file\n");
            return 0;
        }
        if(resizeBuffer(&buf, &bufsz, len + 1) == 0) {
            return 0;
        }
        if(fread(buf, 1, len, sfp) != len) {
            printf("Cannot read temp file\n");
            return 0;
        }
        buf[len] = '\0';
        printf("%ld ", line);
        printf("%s\n", buf);
        bp = bp->forw;
        line++;
    }
    return 1;
}
