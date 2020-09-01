#include "csv_helpers.h"

#include <stdio.h>
#include <string.h>

void strip_nl(char *s) {
  char *c;
  if ((c = strchr(s, '\n'))) *c = '\0';
}

void print_error(const char *func_name, const char *msg) {
  fprintf(stderr, "~> ERROR (%s): %s\n", func_name, msg);
}
