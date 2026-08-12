#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

//Gets a random word from word.txt
void getWord(char* word) {
  srand(time(NULL));
  int count = 0, linenum = rand() % 14855;

  const char* fname = "words.txt";
  FILE* fp = fopen(fname, "r");
  
  if (fp != NULL){
    while (fgets(word, sizeof(word), fp)) {
      if (count == linenum) {
        fclose(fp);
        break;
      } else {
        count++;
      }
    }  
  } else {
    printf("File error");
  }
}

int main() {
  char word[5]; 
  getWord(word);
  printf("%s", word);
}
