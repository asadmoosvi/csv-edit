void strip_nl(char *s);
void print_error(const char *func_name, const char *msg);
char *str_slice(const char *string, int start, int end);
void get_col_start_end(const char *row, int fetch_idx, int *start, int *end);
void print_centered_text(const char *txt, int width);
void print_bar(int ncols, int colwidth);
