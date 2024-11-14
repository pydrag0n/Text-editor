CC=gcc
CFLAGS=-Wall -g

O=out
OBJS = $(O)/buffer.o $(O)/command.o $(O)/io.o $(O)/main_loop.o $(O)/mem.o $(O)/main.o

.PHONY: all clean
all: out $(O)/ed.exe
	$(O)/ed.exe

out:
	mkdir out

$(O)/ed.exe: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(O)/ed.exe

$(O)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
