CC=gcc
CFLAGS=-Wall

O=out
OBJS = $(O)/command.o $(O)/io.o $(O)/main.o #$(O)/color.o

.PHONY: all clean
all: out $(O)/ed.exe
	$(O)/ed.exe

out:
	mkdir out

$(O)/ed.exe: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(O)/ed.exe

$(O)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
