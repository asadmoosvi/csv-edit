CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

all: test

test: test.c csv_reader.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	$(RM) *.o test
