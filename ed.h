typedef struct line
{
    struct line *forw;
    struct line *back;
    long pos;
    long len;
}
line_t;

// ========== [buffer.c] ==========
long currentAddr(void);
long incCurrentAddr(void);
void setCurrentAddr(const long addr);

long lastAddr(void);

char modified(void);
void setModified(const char m);

long incAddr(long addr);
long decAddr(long addr);

void linkNodes(line_t *const prev, line_t *const next);
void insertNode(line_t *const lp, line_t *const prev);

char openSbuf(void);
char closeSbuf(void);
char initBuffer(void);

line_t *dupLineNode(line_t *const lp);
line_t *searchLineNode(const long addr);
void addLineNode(line_t *const lp, const long addr);

char *putSbufLine(char *const buf, const long size, const long addr);
char *getSbufLine(const line_t *const lp);

char appendLines(char **bufp, const long addr);
char deleteLines(const long from, const long to);

// ========== [command.c] ==========
char execCommand(char *s);

// ========== [io.c] ==========
char displayLines(long from, const long to);

char *getLine(long *const sizep);

long read_file(char *const filename, const long addr);
long write_file(const char *const filename, const long from);

// ========== [main_loop.c] ==========
void setFilename(char *const s);
char* getFilename(void);

int mainLoop(void);

// ========== [mem.c] ==========
char resizeBuffer(char **const buf, long *const size, const long min_size);
