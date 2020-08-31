#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void
print_n_char(char c, int n)
{
    for (int i = 0; i < n; i++)
        putchar(c);
    putchar('\n');
}

void
print_usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s csv_filename [true, false]\n", prog_name);
}

bool
str_to_bool(const char *s)
{
    if (strcmp(s, "true") == 0) {
        return true;
    } else if (strcmp(s, "false") == 0) {
        return false;
    } else {
        fprintf(stderr, "~> invalid flag `%s`\n", s);
        fprintf(stderr, "~> valid values are true or false only\n");
        exit(EXIT_FAILURE);
    }
}
