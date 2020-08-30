#include "csv_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 4096

struct csv_reader {
    int rowcount;
    int colcount;
    char *headings;
    char **rows;
    FILE *csv_file;
};

static void
strip_nl(char *s)
{
    char *c;
    if ((c = strchr(s, '\n')))
        *c = '\0';
}

static void
print_error(const char *func_name, const char *msg)
{
    fprintf(stderr, "~> ERROR (%s): %s\n", func_name, msg);
}

struct csv_reader *
init_csv_reader(const char *csv_filename, bool heading)
{
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
        reader->rows = realloc(reader->rows, (reader->rowcount + 1) * sizeof(char *));
        if (reader->rows == NULL) {
            print_error("init_csv_reader", "realloc failed for reader->rows");
            return NULL;
        }
    }

    // get colcount
    char *c = reader->rows[0];
    while (*c) {
        if (*c == ',')
            reader->colcount++;
        c++;
    }
    // last column
    reader->colcount++;


    return reader;
}

int
csv_reader_get_rowcount(struct csv_reader *reader)
{
    return reader->rowcount;
}

int
csv_reader_get_colcount(struct csv_reader *reader)
{
    return reader->colcount;
}

const char *
csv_reader_get_headings(struct csv_reader *reader)
{
    return reader->headings;
}

const char **
csv_reader_get_rows(struct csv_reader *reader)
{
    return (const char **) reader->rows;
}

void
csv_reader_cleanup(struct csv_reader *reader)
{
    free(reader->headings);
    for (int i = 0; i < reader->rowcount; i++) {
        free(reader->rows[i]);
    }
    free(reader->rows);
    fclose(reader->csv_file);
    free(reader);
}
