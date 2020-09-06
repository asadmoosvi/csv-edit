#include <stdio.h>
#include <stdlib.h>

#include "csv_reader.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s csv_filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    csv_reader_t *reader = init_csv_reader(argv[1], true);
    csv_reader_print_table(reader);
    csv_reader_cleanup(reader);
    exit(EXIT_SUCCESS);
}
