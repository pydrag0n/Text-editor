#define ST_ERROR       -1
#define ST_RUN_LOOP     0
#define ST_STOP_LOOP    1


// io.c
long readFile(const char *filename, char **buffer);
long writeFile(char *filename, char *buffer);
short readConsole(char **buffer);

// command.c
char parse(char *s, char **filename, char **buffer);
