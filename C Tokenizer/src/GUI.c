#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

#define LIMIT 100

void main(){
  char a;
  int i;

  List *history = init_history();

  Item *temp;

  while(1){
    char word[LIMIT];
    i = 0;
    printf(">:");

    while((a = getchar()) != '\n'){
      word[i] = a;
      i++;
      putchar(a);
    }

    add_history(history, word);
    printf("\n word input: %d", count_words(word));
    char** tokens = tokenize(word);
    print_tokens(tokens);
  }
  print_history(history);
}
