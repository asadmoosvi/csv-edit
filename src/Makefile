CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
BINDIR = ../bin

all: $(BINDIR)/test

$(BINDIR)/test: test.c csv_reader.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	$(RM) $(BINDIR)/*.o $(BINDIR)/test
