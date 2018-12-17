all: main

main: main.o
	gcc  main.o -o main -lm

main.o: main.c
	clear
	gcc -c main.c -o main.o -Wall -Wextra -O2

mrProper:
	clear
	rm *.o
	rm main

do:
	clear
	./main 8192 16 2 trace.txt

clear:
	clear
