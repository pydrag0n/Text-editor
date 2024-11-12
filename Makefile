CC=gcc
CFLAGS=-Wall

OBJS = command.o io.o main.o

.PHONY: all
all: ed.exe
	ed.exe

ed.exe: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ed.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
