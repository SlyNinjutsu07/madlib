#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"

void print_word_options(file *madlib) {
  for (int i = 1; i <= madlib->num_words; i++)
    printf("{%d}: {\"%s\"}\n", i, madlib->words[0]);
}

void clear_term();
void ask_for_madlib();

int main(void) {

  char buffer[512];
  FILE *f;

  int index = 0;
  file *madlibs = alloc_file("./madlibs");

  printf("WELCOME TO MADLIB PROGRAM IN C {Press ENTER}: ");

  if (getchar() == '\n') {

    while (1) {
      f = fopen(madlibs[index].file_name, "r");
      // File check
      if (f == NULL && index > 0)
        ask_for_madlib();
      else if (f == NULL){
        perror("File doesn't exit");
        return 0;
      }

      read_madlib(f, buffer, 512);//Reads the current file to buffer

      alloc_words(buffer, &madlibs[index]);//Allocates to word_list
      printf("\nMADLIB #%d => You have %d words to fill:\n", index+1, madlibs[index].num_words);
      printf("%s\n", buffer);
      write_madlib(&madlibs[index], buffer, 512);
      printf("\nMadlib #%d Edit:\n%s\n", index+1, buffer);

      printf("Go to next (y/n)? ");
      
      char input[10];
      fgets(input, 10, stdin);
      if (strcmp(input, "y\n") == 0)
        index++;
      else if(strcmp(input, "n\n") == 0){
        printf("Quitting...\n");
        ask_for_madlib();
        exit(0);
      }
      else{
        printf("\nInvalid Input. quitting...\n"); 
        exit(0);
      }
    }
  }

  free_all(madlibs, &get_dir_len);

  return 0;
}

/* Just to clear console */
void clear_term() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void ask_for_madlib(){
  printf("No more available madlibs...\n");
  printf("Would you like to add a new madlib file?(y/n): ");
  char input1[10];
  char i = strcmp(fgets(input1, 10, stdin), "y\n") == 0 ? 'y' : 'n';
  if(i == 'y'){
    char madlib_name[36];
    printf("Input a name for your file: ");
    fgets(madlib_name, 36, stdin);
    add_madlib_file(madlib_name);
  }
}
