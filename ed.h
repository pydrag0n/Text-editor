#include "color.h" // comment this line out to disable color
#ifndef COLOR_MODE

// ================== [error types] ==================
#define MEM_ERROR_TYPE          "Memory allocation error\n"
#define FNF_ERROR_TYPE          "No current filename\n"
#define OPEN_FILE_ERROR_TYPE    "Cannot open output file\n"

// ================== [other] ==================
#define DEFAULT_COMMAND_CHAR        "*"

#endif /* COLOR_MODE */

// ================== [main states] ==================
#define ST_ERROR       -1
#define ST_RUN_LOOP     0
#define ST_STOP_LOOP    1


// ================== [commands type] ==================
#define QUIT_COMMAND                'q'
#define QUIT_INSERT_MODE_COMMAND    '.'
#define WRITE_FILE_COMMAND          'w'
#define READ_FILE_COMMAND           'e'
#define PRINT_BUFFER_COMMAND        'p'
#define ENTER_INSERT_MODE           'a'


// ========== [io.c] ==========
long readFile(void);
long writeFile(void);
long readConsole(void);

// ========== [command.c] ==========
char parse(char *s);

// ========== [main.c] ==========
void setFilename(const char *const s);
char* getFilename(void);

void setBuffer(char *const s);
char* getBuffer(void);

void loop(void);
