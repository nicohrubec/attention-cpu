CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3

SRCS = attention.c test.c lib.c
OBJS = $(SRCS:.c=.o)
HEADERS = lib.h

all: attention test

attention: attention.o lib.o
	$(CC) $(CFLAGS) -o attention attention.o lib.o -lm

attention.o: attention.c $(HEADERS)
	$(CC) $(CFLAGS) -c attention.c -o attention.o

test: test.o lib.o
	$(CC) $(CFLAGS) -o test test.o lib.o -lm

test.o: test.c $(HEADERS)
	$(CC) $(CFLAGS) -c test.c -o test.o

lib.o: lib.c $(HEADERS)
	$(CC) $(CFLAGS) -c lib.c -o lib.o

clean:
	rm -f attention test *.o

.PHONY: all clean