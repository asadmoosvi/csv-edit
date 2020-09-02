#include "csv_helpers.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strip_nl(char *s) {
  char *c;
  if ((c = strchr(s, '\n'))) *c = '\0';
}

void print_error(const char *func_name, const char *msg) {
  fprintf(stderr, "~> ERROR (%s): %s\n", func_name, msg);
}

char *str_slice(const char *string, int start, int end) {
  char *slice = malloc(end - start + 1);
  char *ptr = slice;

  for (int i = start; i < end; i++)
    *ptr++ = string[i];
  *ptr = '\0';

  return slice;
}

void get_col_start_end(const char *row, int fetch_idx, int *start, int *end) {
  int idx = 0;
  int sep_count = 0;

  if (fetch_idx == 0) {
    *start = 0;
  } else {
    while (row[idx]) {
      if (row[idx] == ',')
        sep_count++;
      idx++;
      if (sep_count == fetch_idx)
        break;
    }
    *start = idx;
  }

  while (row[idx] && row[idx] != ',')
    idx++;

  *end = idx;
}
