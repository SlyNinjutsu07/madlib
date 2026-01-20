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

char* displayintro(void){
  return "WELCOME TO MADLIB PROGRAM IN C {Press ENTER}\n";
}
void print_word_options(file *madlib){
  for(int i = 1; i <= madlib->num_words; i++)
    printf("{%d}: {\"%s\"}\n", i, madlib->words[0]);
}
void clear_term();

char *concat_strings(char *s1, char *s2);
void words_to_fill(char *text, file *madlib);
char *read_madlib(FILE *madlib_file, char *buffer, size_t buffer_size);
void write_madlib(file *madlib, char *buffer, size_t buffer_size);

int main(void){
  
  state s = NOT_BEGUN;

  file madlibs[] = {
    {.file_name="madlibs/madlib1.txt"},
  };

  FILE *f = fopen(madlibs[0].file_name, "r");
  //File check
  if(f == NULL){
    perror("File doesn't exit"); 
    return 0; 
  }

  char buffer[512];
  read_madlib(f, buffer, 512);

  printf("%s", displayintro());
  if(getchar() == '\n'){
    s = RUNNING;
    words_to_fill(buffer, &madlibs[0]);
    printf("You have %d words to fill:\n", madlibs[0].num_words);
    printf("%s\n", buffer);
    write_madlib(&madlibs[0], buffer, 512);
    clear_term();
    printf("Final Madlib:\n\n%s\n", buffer);
  }


  return 0;
}

/* Reads the text from the file into the buffer, 
 * and then returns that text */
char *read_madlib(FILE *madlib_file, char *buffer, size_t buffer_size){
  //File check
  if(madlib_file == NULL){
    perror("File doesn't exit"); 
    return ""; 
  }

  size_t i = fread(buffer, sizeof(char), buffer_size, madlib_file);
  buffer[i] = '\0';
  return buffer;
}

/* Returns the # of spots to fill with words,
 * and allocates memory to madlib word list */
void words_to_fill(char *text, file *madlib){
  int count = 0;
  char *p = text; 

  while((p = strstr(p,"----"))){
    count++;
    p+=4;
  }

  /* Allocate memory for a pointer to pointers. (just the pointer, not the pointers) */
  madlib->words = (char **)malloc(count * sizeof(char*));
  //Reserve head node
  char **head = madlib->words;

  for(int i = 0; i < count; i++){
    madlib->words[i] = (char *)malloc(50 * sizeof(char));//Allocate memory for each string   
    strcpy(madlib->words[i], "----");//Assigns the string into the allocated memory address
                                     //doing *words = "----" would completely re-initalize the address location
  }

  madlib->num_words = count;
  madlib->words = head;
}

void write_madlib(file *madlib, char *buffer, size_t buffer_size) {
  char result[buffer_size];
  result[0] = '\0';
  char *p_curr = buffer, *p, **words_head = madlib->words;
  int i = 0;

  while (i < madlib->num_words && (p = strstr(p_curr, "----"))) {
    strncat(result, p_curr, p - p_curr);//Puts the char's from p_curr all the way to p into result

    char input[50];
    input[0] = '{'; 
    printf("Enter word for number %d: ", i+1);
    fgets(&input[1], 49, stdin);
    input[strcspn(input, "\n")] = '}'; //strcspan -> Read input until you find any 
                                       //characters that look like "any-chars-here"

    strcpy(*(madlib->words), input);
    madlib->words++;

    strncat(result, input, strlen(input));//Add the word

    p+=4;//Sets it ahead to later point to next word_insert
    p_curr = p;
    i++;
  }

  strncat(result, p_curr, strlen(p_curr));

  strcpy(buffer, result);//Copy result back to the buffer
  madlib->words = words_head;//Reset head node
}

/* Just to clear console */
void clear_term(){
#ifdef _WIN32
  system("cls");
#else 
  system("clear");
#endif
}

