#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define WORD_COUNT 5
#define FILE_SIZE 14855

enum result {
  INCORRECT, INCLUDED, CORRECT
};

// Gets a random word from word.txt
void getWord(char* word) {
  srand(time(NULL));
  int count = 0, linenum = rand() % FILE_SIZE;

  const char* fname = "words.txt";
  FILE* fp = fopen(fname, "r");
  
  if (fp != NULL){
    while (fgets(word, sizeof(word) - 1, fp)) {
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

// Checks if user input is all letters
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

// Checks if user input is valid
bool isValid(const char* userInput) {
   if (strlen(userInput) != WORD_COUNT) {
    return false; 
  } if (!isLetter(userInput)) {
    return false; 
  } 
  return true;
}

// Checks if given character is in word
bool charInWord(const char* word, const char c) {
  for (int i = 0; i < WORD_COUNT; i++) {
    if (c == word[i]) {
      return true;
    }
  } 
  return false;
}

bool charToChar(const char* word, const char* c, int pos) {
  if (c[pos] == word[pos]) {
    return true;
  }
  return false;
}

// Validates input
void inputValidation(char* userInput, FILE* s) {
  int c;
  while (!isValid(userInput)) {
      printf("Input invalid, please enter valid input: ");
      userInput[strcspn(userInput, "\n")] = 0;
      scanf("%s", userInput);
      while ((c = getchar()) != '\n' && c != EOF);

  }
}

void printIcon(const int arr[]) {
  for (int i = 0; i < WORD_COUNT; i++) {
    switch (arr[i]) {
      case 0:
        printf("🔴");
        break;
      case 1:
        printf("🟡");
        break;
      case 2: 
        printf("️🟢");
        break;
      default: 
        printf("ERROR");
        break;
    }
  }
}

int main() {
  char word[WORD_COUNT+1], userInput[512];
  int guessCount = 1, correct[5] = {0, 0, 0, 0, 0};
  getWord(word);

  printf("Welcome to Wordle, enter a word to start guessing, word is %s", word);
  printf("Guess %d: ", guessCount);
  scanf("%s", userInput);
  //while ((c = getchar()) != '\n' && c != EOF);
  inputValidation(userInput, stdin); 

  while (strncmp(word, userInput, WORD_COUNT) != 0) {
    for (int i = 0; i < sizeof(correct)/sizeof(int) ; i++) {
      if (charToChar(word, userInput, i)) {
        correct[i] = 2;
      } else if (charInWord(word, userInput[i])) {
        correct[i] = 1; 
      } else correct[i] = 0;
    }    
    guessCount++;
    printIcon(correct);
    printf("\nGuess %d: ", guessCount);
    scanf("%s", userInput);
    inputValidation(userInput, stdin);
  }

  printf("Congratulations, the word is: %s", word);

  return 0;
}

