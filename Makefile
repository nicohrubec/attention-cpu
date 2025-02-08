CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: main

main: main.c
	$(CC) $(CFLAGS) -o main main.c

clean:
	rm -f main
