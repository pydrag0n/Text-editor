#include "ed.h"

static long current_addr_ = 0; // current line address in buffer
static long last_addr_ = 0;    // last(head) line address in buffer
static char modified_ = 0;     // if buffer was modified since last read/write

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
