gcc io.c -c -o io.o
gcc main.c -c -o main.o
gcc io.o main.o -o ed.exe
ed.exe
