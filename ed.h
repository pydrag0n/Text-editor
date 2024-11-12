// io.c
long readFile(const char *filename, char **buffer);
long writeFile(char *filename, char *buffer);

// command.c
char parse(char *s, char *filename, char *buffer, char **adbuffer);
