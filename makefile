CC=gcc
CFLAGS=-std=c9x

all: build

build: tema1

tema1: tema1.c coada.h functii.h
	$(CC) $(CFLAGS) tema1.c -g -o tema1
	
run: tema1
	valgrind ./tema1

clean:
	rm -f tema1


