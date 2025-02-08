CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: attention

attention: attention.c
	$(CC) $(CFLAGS) -o attention attention.c

clean:
	rm -f attention
