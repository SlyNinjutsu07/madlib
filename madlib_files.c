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

/* Allows for custom additions to the madlib folder */
void add_madlib_file(char *file_name){
  //Null-checking
  if(!file_name){
    perror("No file\n");
    return;
  }
  else if(strcspn(file_name, "\t\\\"-") != strlen(file_name)){
    perror("Invalid file-name. Ensure there are no:\n-Tabs\n-Backslashes(\"\\\")\n-Em-dashes(\"\\\")\n");
    return;
  }

  file_name[strcspn(file_name, "\n")] = '\0';
  char file_new_name[36];
  snprintf(file_new_name, sizeof file_new_name, "madlibs/%s.txt", file_name);

  FILE *f = fopen(file_new_name,"w");
  char buffer[256];
  buffer[0] = '\0';

  printf("Type out your Madlib (Please look at README for information how to type it out):\n\n");
  fscanf(stdin, "%s", buffer);  
  fwrite(buffer, sizeof buffer, strlen(buffer), f);
}

int main(void){

  char str[16];
  fgets(str, 16, stdin);
  add_madlib_file(str);
  return 0;
}
