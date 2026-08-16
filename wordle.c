#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define WORD_COUNT 5
#define FILE_SIZE 14855

#define GREEN_COLOR "\033[38;5;48m" 
#define YELLOW_COLOR "\033[38;5;214m"
#define RED_COLOR "\033[38;5;196m"  
#define RESET_COLOR "\e[0m"

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

// Checks if given characters match 
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

// Prints colored word to help user
void printHelper(const int arr[], const char* userInput) {
  for (int i = 0; i < WORD_COUNT; i++) {
    switch (arr[i]) {
      case 0:
        printf(RED_COLOR"%c", userInput[i]);
        printf(RESET_COLOR);
        break;
      case 1:
        printf(YELLOW_COLOR"%c", userInput[i]);
        printf(RESET_COLOR);
        break;      
      case 2: 
        printf(GREEN_COLOR"%c", userInput[i]);
        printf(RESET_COLOR);
        break;
    }
  }
  printf("\n");
}

// Fills in the correct array
void fillCorrect(int correct[], const char* word, const char* userInput) {
  for (int i = 0; i < WORD_COUNT; i++) {
    if (charToChar(word, userInput, i)) {
      correct[i] = 2;
    } else if (charInWord(word, userInput[i])) {
      correct[i] = 1;
    } else correct[i] = 0;
  }
}

// Prints player's best attempt
void printBestAttempt(int correct[], char* bestAttempt, const char* word) {
  for (int i = 0; i < WORD_COUNT; i++) {
    switch (correct[i]) {
      case 2:
        bestAttempt[i] = word[i];
        break;
      default:
        if (bestAttempt[i] != word[i]) {
          bestAttempt[i] = '-';
        }
        break;
    }
  }
  printf("%s\n", bestAttempt);
}

// Unlimited wordle gameplay loop
void unlimitedGameplayLoop(const char* word, FILE* stdin) {
  char userInput[512], bestAttempt[WORD_COUNT+1];
  int guessCount = 0, correct[5] = {0, 0, 0, 0, 0};

  while (strncmp(word, userInput, WORD_COUNT) != 0) {
    guessCount++;
    printf("\nGuess %d: ", guessCount);
    scanf("%s", userInput);
    inputValidation(userInput, stdin);
    fillCorrect(correct, word, userInput);
    printHelper(correct, userInput);
    printBestAttempt(correct, bestAttempt, word);
  }
  printf("Congratulations, the word is: %s", word);
}

// Default wordle gameplay loop (5 guesses)
void defaultGameplayLoop(const char* word, FILE* stdin) {
  char userInput[512], bestAttempt[WORD_COUNT+1];
  int guessCount = 0, correct[5] = {0, 0, 0, 0, 0};

  while (strncmp(word, userInput, WORD_COUNT) != 0 && guessCount < 5) {
    guessCount++;
    printf("\n%d guesses left: ", 5 - guessCount + 1);
    scanf("%s", userInput);
    inputValidation(userInput, stdin);
    fillCorrect(correct, word, userInput);
    printHelper(correct, userInput);
    printBestAttempt(correct, bestAttempt, word);
  }
}

int main() {
  int gamemode;
  char word[WORD_COUNT+1]; 
  getWord(word);

  printf("Welcome to Wordle, choose (1) standard or (2) unlimited guess: ");
  scanf("%d", &gamemode);

  switch (gamemode) {
    case 2:
      unlimitedGameplayLoop(word, stdin);
      break;
    default:
      defaultGameplayLoop(word, stdin);
      break;
  }

  return 0;
}

//Todo list: 1. fix word having newline, 2. validate valid word from list, 3. add message for defautl mode
