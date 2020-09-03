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
  char **rows;
  char **misc_data;
  int misc_data_size;
  FILE *csv_file;
};

static void dump_to_misc(struct csv_reader *reader, char *str);

/*
 * Initialize and return a csv_reader object
 * from a csv_filename
 */
struct csv_reader *init_csv_reader(const char *csv_filename, bool heading) {
  FILE *fp = fopen(csv_filename, "r");
  if (fp == NULL) {
    print_error("init_csv_reader", "unable to open csv file");
    exit(EXIT_FAILURE);
  }

  struct csv_reader *reader = malloc(sizeof(struct csv_reader));
  if (reader == NULL) {
    print_error("init_csv_reader", "malloc failed for csv_reader");
    fclose(fp);
    exit(EXIT_FAILURE);
  }

  reader->csv_file = fp;
  reader->rowcount = 0;
  reader->colcount = 0;
  reader->misc_data = NULL;
  reader->misc_data_size = 0;

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
      csv_reader_cleanup(reader);
      exit(EXIT_FAILURE);
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

  for (int i = 0; i < reader->rowcount; i++) {
    free(reader->rows[i]);
  }
  free(reader->rows);

  for (int i = 0; i < reader->misc_data_size; i++) {
    free(reader->misc_data[i]);
  }
  free(reader->misc_data);

  fclose(reader->csv_file);
  free(reader);
}

/*
 * Get a heading name by its index number.
 */
const char *csv_reader_get_heading(struct csv_reader *reader, int i) {
  int heading_start, heading_end;
  char *heading;

  if (i < 0 || i >= reader->colcount) {
    print_error("csv_reader_get_heading", "invalid index");
    fprintf(stderr, "~> index is `%d` (allowable indices are 0 to %d inclusive)\n",
            i, reader->colcount - 1);
    return NULL;
  }

  get_col_start_end(reader->headings, i, &heading_start, &heading_end);
  heading = str_slice(reader->headings, heading_start, heading_end);
  // save heading
  dump_to_misc(reader, heading);

  return heading;
}

/*
 * Save a new string in misc_data.
 */
static void dump_to_misc(struct csv_reader *reader, char *str) {
  reader->misc_data = realloc(reader->misc_data, sizeof(char *) * ++reader->misc_data_size);
  if (reader->misc_data == NULL) {
    print_error("dump_to_misc", "realloc failed");
    csv_reader_cleanup(reader);
    exit(EXIT_FAILURE);
  }

  reader->misc_data[reader->misc_data_size - 1] = str;
}
