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
#define QUIT_COMMAND                'q'
#define QUIT_INSERT_MODE_COMMAND    '.'
#define WRITE_FILE_COMMAND          'w'
#define READ_FILE_COMMAND           'e'
#define PRINT_BUFFER_COMMAND        'p'
#define ENTER_APPEND_MODE           'a'
#define ENTER_INSERT_MODE           'i'
#define SWITCH_COLOR                'C'

// ========== [io.c] ==========
long readFile(void);
long writeFile(void);
long readConsole(char const _Mode);

// ========== [command.c] ==========
char parse(char *s);

// ========== [main_loop.c] ==========
void setFilename(const char *const s);
char* getFilename(void);

void setBuffer(char *const s);
char* getBuffer(void);

void loop(void);

void switchColor(void);

void cprint(char t);
