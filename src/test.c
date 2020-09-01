#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_reader.h"
#include "test_helpers.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *csv_filename = argv[1];
  bool flag;

  flag = str_to_bool(argv[2]);

  csv_reader_t *reader = init_csv_reader(csv_filename, flag);
  if (reader == NULL) {
    fprintf(stderr, "Unable to create csv_reader_t object.\n");
    exit(EXIT_FAILURE);
  }

  const char *headings = csv_reader_get_headings(reader);
  const char **rows = csv_reader_get_rows(reader);
  int colcount = csv_reader_get_colcount(reader);
  int rowcount = csv_reader_get_rowcount(reader);

  if (headings != NULL) printf("headings: %s ", headings);

  printf("(rows: %d, cols: %d)\n", rowcount, colcount);
  int sep_len = 0;
  if (headings) {
    sep_len += 9;
    sep_len += strlen(headings);
  }
  sep_len += 20;
  print_n_char('-', sep_len);

  for (int i = 0; i < rowcount; i++) printf("%s\n", rows[i]);

  csv_reader_cleanup(reader);
  exit(EXIT_SUCCESS);
}
