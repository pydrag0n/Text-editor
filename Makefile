CC=gcc
CFLAGS=-Wall

OBJS = command.o io.o main.o

.PHONY: all clean
all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ed.exe
	ed.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
