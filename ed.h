#include "color.h"

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
#define ST_ERROR       -1
#define ST_RUN_LOOP     0
#define ST_STOP_LOOP    1

// ========== [commands] ==========
#define COMMAND_QUIT                'q'
#define COMMAND_QUIT_INSERT         '.'
#define COMMAND_WRITE_FILE          'w'
#define COMMAND_READ_FILE           'e'
#define COMMAND_PRINT_BUFFER        'p'
#define COMMAND_APPEND              'a'
#define COMMAND_INSERT              'i'
#define COMMAND_COLOR               'C'

// ========== [command.c] ==========
char parse(char *s);

// ========== [io.c] ==========
long readFile(void);
long writeFile(void);
long readConsole(char const _Mode);
void printBuffer(void);

// ========== [main_loop.c] ==========
void setFilename(char *const s);
char* getFilename(void);

void setBuffer(char *const s);
char* getBuffer(void);

void setBufferTop(char *const s);
char* getBufferTop(void);

void switchColor(void);

void cprint(char t);

void loop(void);
