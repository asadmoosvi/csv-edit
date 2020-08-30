CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
BINDIR = ../bin

all: test

test: test.c csv_reader.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

.PHONY: clean

clean:
	$(RM) $(BINDIR)/*.o $(BINDIR)/test
