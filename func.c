#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"

/* Frees all memory */
void free_all(file arr[], int size){
  file *p = arr;
  for(int i = 0; i < size; i++){
    free(p);
    p++;
  }
}

/* Returns the # of spots to fill with words,
 * and allocates memory to madlib word list */
void alloc_words(char *text, file *madlib) {
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
  }

  madlib->num_words = count;
  madlib->words = head; // Send back to first pointer in arr
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


void write_madlib(file *madlib, char *buffer, size_t buffer_size) {
  char result[buffer_size];
  result[0] = '\0';
  char *p_curr = buffer, *p = NULL, **words_head = madlib->words;
  int i = 0;

  while ((p = strstr(p_curr, "----"))) {
    strncat(
        result, p_curr,
        p - p_curr); // Puts the char's from p_curr all the way to p into result

    char input[50];
    printf("Enter word for number %d: ", i + 1);

    input[0] = '{';
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



