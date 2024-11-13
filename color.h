#define DEF_COLOR_MODE 0
#define COLOR_MODE 1

#define COLOR_END                   "\x1b[0m"

#define TEXT_COLOR_RED              "\x1b[31m" 
#define TEXT_COLOR_GREEN            "\x1b[32m"
#define TEXT_COLOR_YELLOW           "\x1b[33m"
#define TEXT_COLOR_BLUE             "\x1b[34m"
#define TEXT_COLOR_PURPLE           "\x1b[35m"
#define TEXT_COLOR_WHITE            "\x1b[37m"

#define BACKGROUND_COLOR_RED        "\x1b[41m"
#define BACKGROUND_COLOR_GREEN      "\x1b[42m"
#define BACKGROUND_COLOR_YELLOW     "\x1b[43m"
#define BACKGROUND_COLOR_BLUE       "\x1b[44m"
#define BACKGROUND_COLOR_PURPLE     "\x1b[45m"
#define BACKGROUND_COLOR_WHITE      "\x1b[47m"

#define MEM_ERROR_TYPE          "%sMemory allocation error\n%s",    BACKGROUND_COLOR_RED, COLOR_END
#define FNF_ERROR_TYPE          "%sNo current filename\n%s",        BACKGROUND_COLOR_RED, COLOR_END
#define OPEN_FILE_ERROR_TYPE    "%sCannot open output file\n%s",    BACKGROUND_COLOR_RED, COLOR_END

#define DEFAULT_COMMAND_CHAR    "%s*%s",    TEXT_COLOR_GREEN, COLOR_END
