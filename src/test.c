#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "csv_reader.h"

void
print_n_char(char c, int n)
{
    for (int i = 0; i < n; i++)
        putchar(c);
    putchar('\n');
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s csv_filename [true, false]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *csv_filename = argv[1];
    bool flag;

    if (strcmp(argv[2], "true") == 0) {
        flag = true;
    } else if (strcmp(argv[2], "false") == 0) {
        flag = false;
    } else {
        fprintf(stderr, "~> invalid flag `%s`\n", argv[2]);
        fprintf(stderr, "~> valid values are true or false only\n");
        exit(EXIT_FAILURE);
    }

    csv_reader_t *reader = init_csv_reader(csv_filename, flag);
    if (reader == NULL) {
        fprintf(stderr, "Unable to create csv_reader_t object.\n");
        exit(EXIT_FAILURE);
    }

    const char *headings = csv_reader_get_headings(reader);
    const char **rows = csv_reader_get_rows(reader);
    int colcount = csv_reader_get_colcount(reader);
    int rowcount = csv_reader_get_rowcount(reader);

    if (headings != NULL)
        printf("headings: %s ", headings);

    printf("(rows: %d, cols: %d)\n", rowcount, colcount);
    int sep_len = 0;
    if (headings) {
        sep_len += 9;
        sep_len += strlen(headings);
    }
    sep_len += 20;
    print_n_char('-', sep_len);

    for (int i = 0; i < rowcount; i++)
        printf("%s\n", rows[i]);

    csv_reader_cleanup(reader);
    exit(EXIT_SUCCESS);
}
