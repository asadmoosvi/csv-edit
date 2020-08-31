CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
BINDIR = ../bin

TEST_SRCS = test.c csv_reader.c test_helpers.c
TEST_DEPS = csv_reader.h test_helpers.h
TEST_EXE = test

all: $(BINDIR)/$(TEST_EXE)

$(BINDIR)/$(TEST_EXE): $(TEST_SRCS) $(TEST_DEPS)
	$(CC) $(CFLAGS) -o $@ $(TEST_SRCS)

.PHONY: clean

clean:
	$(RM) $(BINDIR)/*.o $(BINDIR)/test
