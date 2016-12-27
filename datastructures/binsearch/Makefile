CC = gcc -Wall -pedantic -std=c99

benchmark:
	$(CC) benchmark.c -o benchmark -lm

debug:
	$(CC) -g debug_veb.c -o debug -lm

test:
	$(CC) -g test.c -o test -lm

all: benchmark debug test

clean:
	rm -rf test debug benchmark

