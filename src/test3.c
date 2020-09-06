#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "csv_reader.h"

int main(void) {
    csv_reader_t *reader = init_csv_reader("users.csv", true);
    const char *h1, *h2, *h3, *h4;

    h1 = csv_reader_get_heading(reader, 0);
    printf("h1: %s\n", h1);

    h2 = csv_reader_get_heading(reader, 1);
    printf("h2: %s\n", h2);

    h3 = csv_reader_get_heading(reader, 2);
    printf("h3: %s\n", h3);

    h4 = csv_reader_get_heading(reader, 3);
    printf("h4: %s\n", h4);

    printf("final headings: %s %s %s %s\n", h1, h2, h3, h4);

    h4 = csv_reader_get_heading(reader, -1);

    csv_reader_cleanup(reader);
    return 0;
}
