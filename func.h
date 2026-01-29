#include <stdio.h>

#include "madlib_files.h"

void free_all(file arr[], int size);

void words_to_fill(char *text, file *madlib);
void read_madlib(FILE *madlib_file, char *buffer, size_t buffer_size);
void write_madlib(file *madlib, char *buffer, size_t buffer_size);

