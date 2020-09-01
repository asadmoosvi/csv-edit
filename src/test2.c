#include <stdio.h>
#include <stdlib.h>

#include "csv_reader.h"
#include "test_helpers.h"

void test_heading_at_idx(csv_reader_t *reader, int i) {
  const char *heading;
  heading = csv_reader_get_heading(reader, i);
  printf("Heading at index `%d` --> `%s`\n", i, heading);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  const char *csv_filename = argv[1];
  bool flag;
  flag = str_to_bool(argv[2]);
  csv_reader_t *reader = init_csv_reader(csv_filename, flag);
  const char *headings;
  const char **rows;
  int colcount = csv_reader_get_colcount(reader);
  headings = csv_reader_get_headings(reader);
  rows = csv_reader_get_rows(reader);

  if (headings) {
    printf("Headings -> %s\n", headings);
  }

  for (int i = 0; i < csv_reader_get_rowcount(reader); i++) {
    printf("------> %s\n", rows[i]);
  }

  const char *heading;

  // test forward
  for (int i = 0; i < colcount; i++) {
    test_heading_at_idx(reader, i);
  }
  printf("--------------------------------------------\n");
  // test reverse
  for (int i = colcount - 1; i >= 0; i--) {
    heading = csv_reader_get_heading(reader, i);
    printf("Heading at index `%d` --> `%s`\n", i, heading);
  }
  printf("--------------------------------------------\n");
  // test in a random  order
  test_heading_at_idx(reader, 0);
  test_heading_at_idx(reader, 3);
  test_heading_at_idx(reader, 1);
  test_heading_at_idx(reader, 2);

  // test out of bound
  test_heading_at_idx(reader, -1);
  csv_reader_cleanup(reader);
  exit(EXIT_SUCCESS);
}
