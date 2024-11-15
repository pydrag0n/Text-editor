#include "color.h"

typedef struct line
{
    struct line *forw;
    struct line *back;
    long pos;
    long len;
}
line_t;

// ========== [print codes] ==========
#define COMMAND_CODE         0
#define ERROR_CODE_MEM       1
#define ERROR_CODE_FILENAME  2
#define ERROR_CODE_OPEN      3

// ========== [print messages] ==========
#define COMMAND_CHAR           "*"
#define ERROR_MSG_MEM          "Memory allocation error\n"
#define ERROR_MSG_FILENAME     "No current filename\n"
#define ERROR_MSG_OPEN         "Cannot open output file\n"

// ========== [main states] ==========
#define QUIT           -1

// ========== [commands] ==========
#define COMMAND_QUIT                'q'
#define COMMAND_QUIT_INSERT         '.'
#define COMMAND_WRITE_FILE          'w'
#define COMMAND_READ_FILE           'e'
#define COMMAND_PRINT_BUFFER        'p'
#define COMMAND_APPEND              'a'
#define COMMAND_INSERT              'i'
#define COMMAND_COLOR               'C'

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
char appendLines(char **bufp, const long addr);

// ========== [command.c] ==========
char execCommand(char *s);

// ========== [io.c] ==========
long readFile(void);
long writeFile(void);
long readConsole(char const _Mode);
void printBuffer(void);
char* getLine(long *const sizep);

// ========== [main_loop.c] ==========
void setFilename(char *const s);
char* getFilename(void);

void setBuffer(char *const s);
char* getBuffer(void);

void setBufferTop(char *const s);
char* getBufferTop(void);

void switchColor(void);

void cprint(char t);

int mainLoop(void);

// ========== [mem.c] ==========
char resizeBuffer(char **const buf, long *const size, const long min_size);
