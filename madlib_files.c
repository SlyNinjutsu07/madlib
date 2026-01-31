#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "madlib_files.h"

/* Return a file* that points to the list of madlibs */
file **alloc_file(char *path){
  DIR *dir = opendir(path);
  if(!dir){
    perror("No valid directory\n");
    return NULL;
  }

  struct dirent *entry;
  int file_count;

  /* Count how many .txt files there are */
  while((entry = readdir(dir))!= NULL)
    if(strstr(entry->d_name, ".txt"))
      file_count++;
  if(!file_count) return NULL;

  file *madlibs = (file *)malloc(file_count * sizeof(file)), *tail = madlibs;
  char full_path[256];
  full_path[0] = '\0';
  strncat(full_path, path, strlen(path));
  

  while((entry = readdir(dir))!= NULL){
    if(strstr(entry->d_name, ".txt")){
      tail->file_name = strncat(full_path, entry->d_name, strlen(entry->d_name));
      printf("%s\n", full_path);
      tail++;
    }
  }

  closedir(dir);

  return &madlibs;
}
