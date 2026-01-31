#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "madlib_files.h"

file *alloc_file(char *folder){
  DIR *dir = opendir(folder);
  if(!dir){
    perror("No valid directory\n");
    return NULL;
  }

  struct dirent *entry;
  file *madlibs, *tail; 

  while((entry = readdir(dir)) != NULL){
    madlibs = (file *)malloc(sizeof(char));
    tail = madlibs;
    if(strstr(entry->d_name, ".txt")){
      tail->file_name = entry->d_name;
      madlibs++;
      madlibs = (file *)malloc(sizeof(file));
    }
  }

  return madlibs;
}
