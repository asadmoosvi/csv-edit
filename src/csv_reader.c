#include "csv_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_helpers.h"

#define LINE_LEN 4096

struct csv_reader {
  int rowcount;
  int colcount;
  char *headings;
  char *heading;
  char **rows;
  FILE *csv_file;
};

/*
 * Initialize and return a csv_reader object
 * from a csv_filename
 */
struct csv_reader *init_csv_reader(const char *csv_filename, bool heading) {
  FILE *fp = fopen(csv_filename, "r");
  if (fp == NULL) {
    print_error("init_csv_reader", "unable to open csv file");
    return NULL;
  }

  struct csv_reader *reader = malloc(sizeof(struct csv_reader));
  if (reader == NULL) {
    print_error("init_csv_reader", "malloc failed for csv_reader");
    fclose(fp);
    return NULL;
  }

  reader->csv_file = fp;
  reader->rowcount = 0;
  reader->colcount = 0;
  reader->heading = NULL;

  char line_buf[LINE_LEN];

  // get heading if asked for
  if (heading) {
    if (fgets(line_buf, LINE_LEN, fp)) {
      strip_nl(line_buf);
      reader->headings = malloc(strlen(line_buf) + 1);
      strcpy(reader->headings, line_buf);
    }
  } else {
    reader->headings = NULL;
  }

  // get rows
  reader->rows = malloc(sizeof(char *));
  while (fgets(line_buf, LINE_LEN, fp)) {
    strip_nl(line_buf);
    reader->rows[reader->rowcount] = malloc(strlen(line_buf) + 1);
    strcpy(reader->rows[reader->rowcount], line_buf);
    reader->rowcount++;
    reader->rows =
        realloc(reader->rows, (reader->rowcount + 1) * sizeof(char *));
    if (reader->rows == NULL) {
      print_error("init_csv_reader", "realloc failed for reader->rows");
      return NULL;
    }
  }

  // get colcount
  char *c = reader->rows[0];
  while (*c) {
    if (*c == ',') reader->colcount++;
    c++;
  }
  // last column
  reader->colcount++;

  return reader;
}

/*
 * Number of rows in CSV file (excluding the headings)
 */
int csv_reader_get_rowcount(struct csv_reader *reader) {
  return reader->rowcount;
}

/*
 * Number of columns in CSV file
 */
int csv_reader_get_colcount(struct csv_reader *reader) {
  return reader->colcount;
}

/*
 * Get raw headings, unedited from CSV file
 */
const char *csv_reader_get_headings(struct csv_reader *reader) {
  return reader->headings;
}

/*
 * Get raw rows, unedited from CSV file
 */
const char **csv_reader_get_rows(struct csv_reader *reader) {
  return (const char **)reader->rows;
}

/*
 * Cleanup csv_reader_object's resources
 */
void csv_reader_cleanup(struct csv_reader *reader) {
  free(reader->headings);
  free(reader->heading);
  for (int i = 0; i < reader->rowcount; i++) {
    free(reader->rows[i]);
  }
  free(reader->rows);
  fclose(reader->csv_file);
  free(reader);
}

/*
 * Get a heading name by index number
 */
const char *csv_reader_get_heading(struct csv_reader *reader, int i) {
  int current_idx = 0;

  // check if i is valid
  if (i < 0 || i >= reader->colcount) {
    print_error("csv_reader_get_heading", "invalid index");
    fprintf(stderr,
            "~> index received `%d` (valid indices are between 0 and %d "
            "inclusive)\n",
            i, reader->colcount - 1);
    csv_reader_cleanup(reader);
    exit(EXIT_FAILURE);
  }

  char *heading_start;
  free(reader->heading);
  reader->heading = malloc(strlen(reader->headings) + 1);
  strcpy(reader->heading, reader->headings);
  heading_start = reader->heading;

  char *token;
  if (current_idx == 0) token = strtok(reader->heading, ",");

  while (current_idx != i) {
    token = strtok(NULL, ",");
    current_idx++;
  }

  while (*token) *heading_start++ = *token++;
  *heading_start = '\0';

  return reader->heading;
}
