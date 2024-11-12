gcc io.c -c -o io.o
gcc command.c -c -o command.o
gcc main.c -c -o main.o
gcc io.o command.c main.o -o ed.exe
ed.exe
