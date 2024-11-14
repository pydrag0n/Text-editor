#include <stdio.h>

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
void setCurrentAddr(const int addr) { current_addr_ = addr; }

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

char initBuffer(void)
{
    if(openSbuf() == 0) {return 0;}
    linkNodes(&buffer_head, &buffer_head);
    return 1;
}

line_t* dupLineNode(line_t *const lp)
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
