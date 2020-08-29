#include <stdbool.h>

typedef struct csv_reader csv_reader_t;
csv_reader_t *init_csv_reader(const char *csv_filename, bool heading);
const char *csv_reader_get_headings(csv_reader_t *reader);
int csv_reader_get_rowcount(csv_reader_t *reader);
int csv_reader_get_colcount(csv_reader_t *reader);
bool csv_reader_cleanup(csv_reader_t *reader);
const char **csv_reader_get_rows(csv_reader_t *reader);
