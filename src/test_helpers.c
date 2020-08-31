#include <stdio.h>

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
