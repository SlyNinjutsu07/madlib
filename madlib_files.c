#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "madlib_files.h"

/* Return a file* that points to the list of madlibs */
file *alloc_file(char *path) {
  DIR *dir = opendir(path);
  if (!dir) {
    perror("No valid directory\n");
    return NULL;
  }

  struct dirent *entry;
  int file_count = 0;

  /* Count how many .txt files there are */
  while ((entry = readdir(dir)) != NULL)
    if (strstr(entry->d_name, ".txt"))
      file_count++;

  if (!file_count) {
    closedir(dir);
    return NULL;
  }

  rewinddir(dir);//Resets to first entry

  file *madlibs = (file *)malloc(file_count * sizeof(file)), *tail = madlibs;
  char full_path[512];

  while ((entry = readdir(dir)) != NULL) {
    if (strstr(entry->d_name, ".txt")) {
      snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
      tail->file_name = strdup(full_path);
      tail++;
    }
  }

  closedir(dir);

  return madlibs;
}

void make_file(char *file_name){
  if(!file_name){
    perror("No file\n");
    return;
  }
  else if(strcspn(file_name, "\n\t\\\"-") != strlen(file_name)){
    perror("Invalid file-name. Ensure there are no:\n-New Lines\n-Tabs\n-Backslashes(\"\\\")\n-Em-dashes(\"\\\")\n");
    return;
  }

  FILE *f = fopen(strncat(file_name, ".txt", strlen(".txt")),"w");
  char *buffer[256];

}


