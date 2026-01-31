#include <stdio.h>

typedef struct {
  char *file_name;
  char **words;
  int num_words;
} file;

file *alloc_file(char *path);

void add_madlib_file(char *file_name);
