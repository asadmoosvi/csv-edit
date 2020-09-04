CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c99 -fpic
BINDIR = ../bin

SRCS = csv_reader.c csv_helpers.c test_helpers.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.h)

SHARED_LIB = libcsv-edit.so
TESTS_EXE = test test2 test3

all: $(TESTS_EXE)

$(TESTS_EXE): $(OBJS) $(TEST_DEPS)

lib: $(SHARED_LIB)

$(SHARED_LIB): $(OBJS)
	$(CC) $(CFLAGS) --shared -fpic -o libcsv-edit.so $(OBJS)

.PHONY: clean

clean:
	$(RM) $(TESTS_EXE) $(OBJS) $(SHARED_LIB)
