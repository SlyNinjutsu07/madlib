#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir("./madlibs");
  if (dir == NULL) {
    perror("Invalid directory\n");
    return 1;
  }

  while ((entry = readdir(dir)) != NULL)
    if (strstr(entry->d_name, ".txt"))
      printf("File: %s\n", entry->d_name);

  printf("Hello, world\n");

  return 0;
}
