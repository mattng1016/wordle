#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

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

//Checks if user input is all letters
bool isLetter(const char* userInput) {
  int i = 0;
  while (userInput[i] != '\0') {
    if (!isalpha(userInput[i])) {
      return false;
    }
    i++;
  } 
  return true;
}

//Checks if user input is valid
bool isValid(const char* userInput) {
   if (strlen(userInput) != 5) {
    return false; 
  } if (!isLetter(userInput)) {
    return false; 
  } 
  return true;
}

int main() {
  char word[6], userInput[6];
  int guessCount;
  getWord(word);

  printf("Welcome to Wordle, enter a word to start guessing\n");
  fgets(userInput, sizeof(userInput), stdin);

  while (!isValid(userInput)) {
    printf("Input invalid, please enter valid input\n");
    userInput[strcspn(userInput, "\n")] = 0;
    fgets(userInput, sizeof(userInput), stdin);
  } 
  
  printf("Valid input");
  return 0;
}

