CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
BINDIR = ../bin

SRCS = csv_reader.c csv_helpers.c test_helpers.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.h)

TESTS_EXE = test

all: $(TESTS_EXE)

$(TESTS_EXE): $(OBJS) $(TEST_DEPS)

.PHONY: clean

clean:
	$(RM) $(TESTS_EXE) $(OBJS)
