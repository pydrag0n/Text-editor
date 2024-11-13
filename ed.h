#include "color.c"
#ifndef COLOR_MODE


// ================== [error types] ==================
#define MEM_ERROR_TYPE          "%sMemory allocation error\n%s",    BACKGROUND_COLOR_RED, COLOR_END
#define FNF_ERROR_TYPE          "%sNo current filename\n%s",        BACKGROUND_COLOR_RED, COLOR_END
#define OPEN_FILE_ERROR_TYPE    "%sCannot open output file\n%s",    BACKGROUND_COLOR_RED, COLOR_END

// ================== [other] ==================
#define DEFAULT_COMMAND_CHAR    "%s*%s",    TEXT_COLOR_GREEN, COLOR_END

#else

// ================== [error types] ==================
#define MEM_ERROR_TYPE          "Memory allocation error\n"
#define FNF_ERROR_TYPE          "No current filename\n"     // file not found error type
#define OPEN_FILE_ERROR_TYPE    "Cannot open output file\n"

// ================== [other] ==================
#define DEFAULT_COMMAND_CHAR        "*"     // symbol in command reading mode

#endif

// [main states]
#define ST_ERROR       -1
#define ST_RUN_LOOP     0
#define ST_STOP_LOOP    1


// ================== [commands type] ==================
#define QUIT_COMMAND                'q'
#define QUIT_INSERT_MODE_COMMAND    '.'
#define WRITE_FILE_COMMAND          'w'
#define READ_FILE_COMMAND           'e'
#define READ_BUFFER_COMMAND         'p'
#define ENTER_INSERT_MODE           'a'

// ================== [io.c] ==================
long readFile(const char *filename, char **buffer);
long writeFile(char *filename, char *buffer);
short readConsole(char **buffer);

// ================== [command.c] ==================
char parse(char *s, char **filename, char **buffer);
