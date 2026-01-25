#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *file_name;
  char **words;
  int num_words;
} file;

typedef enum {
  NOT_BEGUN,
  RUNNING,
  END,
} state;

char *displayintro(void) {
  return "WELCOME TO MADLIB PROGRAM IN C {Press ENTER}\n";
}
void print_word_options(file *madlib) {
  for (int i = 1; i <= madlib->num_words; i++)
    printf("{%d}: {\"%s\"}\n", i, madlib->words[0]);
}

void clear_term();
void free_all(file arr[], int size);

void words_to_fill(char *text, file *madlib);
void read_madlib(FILE *madlib_file, char *buffer, size_t buffer_size);
void write_madlib(file *madlib, char *buffer, size_t buffer_size);

int main(void) {

  state s = NOT_BEGUN;
  char buffer[512], input[2];
  FILE *f;

  int index = 0;
  file madlibs[] = {
      {.file_name = "madlibs/madlib1.txt"},
      {.file_name = "madlibs/madlib2.txt"},
      {.file_name = "madlibs/madlib3.txt"},
  };

  printf("%s", displayintro());

  if (getchar() == '\n') {
    s = RUNNING;

    while (s == RUNNING) {
      f = fopen(madlibs[index].file_name, "r");
      // File check
      if (f == NULL) {
        perror("File doesn't exit");
        return 0;
      }

      read_madlib(f, buffer, 512);//Reads the current file to buffer

      words_to_fill(buffer, &madlibs[index]);//Allocates to word_list
      printf("MADLIB #%d: You have %d words to fill:\n", index+1, madlibs[index].num_words);
      printf("%s\n", buffer);
      write_madlib(&madlibs[index], buffer, 512);
      printf("\nMadlib #%d:\n%s\n", index+1, buffer);

      printf("Go to next (y/n)? ");
      
      if (strcmp(fgets(input, 2, stdin), "y\n") == 0)
        index++;
      else if(strcmp(fgets(input, 2, stdin), "n\n") == 0) system("exit");
      else exit(0);
    }
  }

  return 0;
}

/* Reads the text from the file into the buffer,
 * and then returns that text */
void read_madlib(FILE *madlib_file, char *buffer, size_t buffer_size) {
  // File check
  if (madlib_file == NULL) {
    perror("File doesn't exit");
  }

  size_t i = fread(buffer, sizeof(char), buffer_size, madlib_file);
  buffer[i] = '\0';
}

/* Returns the # of spots to fill with words,
 * and allocates memory to madlib word list */
void words_to_fill(char *text, file *madlib) {
  int count = 0;
  char *p = text;

  while ((p = strstr(p, "----"))) {
    count++;
    p += 4;
  }

  /* Allocate memory for a pointer to pointers. (just the pointer, not the
   * pointers) */
  madlib->words = (char **)malloc(count * sizeof(char *));
  // Reserve head node
  char **head = madlib->words;

  for (int i = 0; i < count; i++) {
    madlib->words[i] =
        (char *)malloc(50 * sizeof(char)); // Allocate memory for each string
    strcpy(madlib->words[i],
           "----"); // Assigns the string into the allocated memory address
                    // doing *words = "----" would completely re-initalize the
                    // address location
  }

  madlib->num_words = count;
  madlib->words = head; // Send back to first pointer in arr
}

void write_madlib(file *madlib, char *buffer, size_t buffer_size) {
  char result[buffer_size];
  result[0] = '\0';
  char *p_curr = buffer, *p, **words_head = madlib->words;
  int i = 0;

  getchar();
  while (i < madlib->num_words && (p = strstr(p_curr, "----"))) {
    strncat(
        result, p_curr,
        p - p_curr); // Puts the char's from p_curr all the way to p into result

    char input[50];
    input[0] = '{';
    printf("Enter word for number %d: ", i + 1);
    fgets(&input[1], 49, stdin);
    input[strcspn(input, "\n")] =
        '}'; // strcspan -> Read input until you find any
             // characters that look like "any-chars-here"

    strcpy(*(madlib->words), input);
    madlib->words++;

    strncat(result, input, strlen(input)); // Add the word

    p += 4; // Sets it ahead to later point to next word_insert
    p_curr = p;
    i++;
  }

  strncat(result, p_curr, strlen(p_curr));

  strcpy(buffer, result);     // Copy result back to the buffer
  madlib->words = words_head; // Reset head node
}

/* Just to clear console */
void clear_term() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void free_all(file arr[], int size){
  
}
