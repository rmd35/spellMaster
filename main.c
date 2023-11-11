#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

// Define the structure for a linked list node
typedef struct wordNode {
    char word[50];
    struct wordNode* next;
} wordNode;

/////////////// Function Declarations ///////////////

void insert(char wordToInsert[], wordNode* array[]);
char* botSpell(wordNode *head, int *count, const char level[]);
void displayEffect();
void displayStart(char name1[], char name2[]);
int wordsStartingWithChar(char *words[], char c, int sizeOfArray);
void toLowerCase(char word[]);
int isFound(char word[], char *array[], int size);
int sameLetter(char* oldWord, char* newWord);
void printWords(char *words[], int sizeOfArray);

////////////////////////// MAIN /////////////////////////

int main() {
    FILE *file;
    int wordCount;
    char fileName[] = "spells.txt";
    file = fopen(fileName, "r"); // Reading the file

    // Check if the file is empty
    if (file == NULL) {
        printf("Strange, your spellbook is missing! \n");
        return 0;
    }

    // Read the number of words from the file
    if (fscanf(file, "%d", &wordCount) != 1) {
        printf("Invalid file format. Unable to read word count.\n");
        fclose(file);
        return 0;
    }

    // Allocate memory for storing words
    char **words = (char **)malloc(wordCount * sizeof(char *));
    if (words == NULL) {
        printf("Memory allocation error for words array.\n");
        fclose(file);
        return 0;
    }

    // Initialize variables for letter frequencies and linked lists
    int alphabet = 26;
    int lastLetterCounter[alphabet];
    for (int i = 0; i < alphabet; i++) {
        lastLetterCounter[i] = 0;
    }
    wordNode* letteredwords[alphabet];
    for (int i = 0; i < alphabet; i++) {
        letteredwords[i] = NULL;
    }

    // Read words from the file and populate arrays
    for (int i = 0; i < wordCount; i++) {
        char word[100];
        if (fscanf(file, "%s", word) != 1) {
            printf("Error reading word from the file.\n");
            fclose(file);
            free(words);
            return 0;
        }
        toLowerCase(word);
        words[i] = strdup(word);
        int indexOfLetter = word[0] - 'a';
        lastLetterCounter[indexOfLetter]++;
        insert(word, letteredwords);
    }
    fclose(file); // Close the file after reading

    ///////////////////// BEGIN THE GAME /////////////////////

    displayEffect();

    char player1[50];
    char player2[] = "Grindlewald";
    char level[10];

    printf("Enter your wizard name: ");
    scanf("%s", player1);

    printf("How difficult would you like the game to be? (easy/hard): ");
    scanf("%s", level);

    srand(time(NULL));
    int random = rand() % 2; // Toss the coin

    printf("The fates have conspired, the wands have been chosen, and now, it's time to decide who will cast the first spell...\n\n");
    sleep(2);
    printf("Let us toss a galleon and see who the laws of arithmancy favor!\n\n");
    sleep(2);

    char Playing[50]; // Contains the name of whoever is playing
    if (random == 0) {
        printf("By the powers of the Elder Wand, %s shall commence this duel!\n\n", player1);
        sleep(2);
        displayStart(player1, player2);
        strcpy(Playing, player1);
    } else {
        printf("By the grace of Merlin's beard, %s shall kick things off!\n\n", player2);
        sleep(2);
        displayStart(player2, player1);
        strcpy(Playing, player2);
    }

    // Create an array that stores the words chosen
    char **chosenWords = (char **)malloc(wordCount * sizeof(char *));
    if (chosenWords == NULL) {
        printf("Memory allocation error for chosenWords\n");
        for (int i = 0; i < wordCount; i++) {
            free(chosenWords[i]);
        }
        free(chosenWords); // In case the array is full, clean up previous memory allocation
        return 1;
    }
    for (int i = 0; i < wordCount; i++) {
        chosenWords[i] = NULL;
    }

    int turnCount = 0;
    printWords(words, wordCount);
    char retaliate[80];

    // Do-while loop to keep the game running until someone loses
    do {
        printf("What is your next move?\n");
        if (random != 0) {
           
            int randomIndex = rand() % wordCount;
            strcpy(retaliate, words[randomIndex]);
            random = 0;
        } else {
            if (strcmp(Playing, player1) == 0) {
                scanf("%s", retaliate);
            } else {
                char lastLetter = retaliate[strlen(retaliate) - 1];
                strcpy(retaliate, botSpell(letteredwords[lastLetter - 'a'], lastLetterCounter, level));
            }
        }
        toLowerCase(retaliate);

        if (chosenWords[turnCount] != NULL) {
            // Clean up memory and exit
            for (int i = 0; i < turnCount; i++) {
                free(chosenWords[i]);
            }
            free(chosenWords);
            free(words);
            return 1;
        }
        if (turnCount >= wordCount) {
            printf("mafi mahal\n");
            break;
        }

        printf("%s casted this spell: %s\n", Playing, retaliate);
        chosenWords[turnCount] = strdup(retaliate);
        turnCount++;

        if (!isFound(retaliate, words, wordCount) || !wordsStartingWithChar(words, retaliate[strlen(retaliate) - 1], wordCount) ||
            (turnCount >= 2 && !sameLetter(chosenWords[turnCount - 2], retaliate)) || isFound(retaliate, chosenWords, turnCount - 1)) {
            break;
        }

        // Switch turns only if the current player made a valid move
        if (strcmp(Playing, player1) == 0)
            strcpy(Playing, player2);
        else
            strcpy(Playing, player1);

    } while (1);

    /////////////////////// GAME OVER ///////////////////////

    // Now we announce who the loser is and the condition that broke the loop
    if (isFound(retaliate, chosenWords, turnCount - 1) == 1)
        printf("Such lack of creativity! This spell has been used! %s loses!\n", Playing);
    else if (isFound(retaliate, words, wordCount) == 0)
        printf("%s casts a spell unknown! Such a wonky move! %s loses!\n", Playing, Playing);
    else if (wordsStartingWithChar(words, retaliate[strlen(retaliate) - 1], wordCount) == 0) {
        if (strcmp(Playing, player1) == 0)
            strcpy(Playing, player2);
        else
            strcpy(Playing, player1);
        printf("It seems the odds were against you, %s. The English lexicon has betrayed thee.\n", Playing);
    } else if (sameLetter(chosenWords[turnCount - 2], retaliate) == 0)
        printf("%s offends the laws of the duel! The letters match not! Read for Merlin and Morgana's sake!\n", Playing);

    // Free up memory
    for (int i = 0; i < turnCount; i++) {
        free(chosenWords[i]);
    }
    free(chosenWords);
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}

// Function to insert a word into a linked list
void insert(char wordToInsert[], wordNode* array[]) {
    int index = wordToInsert[0] - 'a';
    wordNode* newNode = malloc(sizeof(wordNode));
    strcpy(newNode->word, wordToInsert);
    newNode->next = array[index];
    array[index] = newNode;
}

// Function to suggest a spell based on frequency and difficulty level
char* botSpell(wordNode *head, int *count, const char level[]) {
    int maximumcount = 0;
    int minimumcount = INT_MAX; // Set to maximum possible value
    char *wordChosen = NULL;
    wordNode *currentLinkedList = head;
    while (currentLinkedList != NULL) {
        char *word = currentLinkedList->word;
        char lastLetter = tolower(word[strlen(word) - 1]);
        int frequency = count[lastLetter - 'a'];
        if (strcmp(level, "easy") == 0) {
            if (frequency >= maximumcount) {
                maximumcount = frequency;
                free(wordChosen);
                wordChosen = strdup(word);
            }
        } else if (strcmp(level, "hard") == 0) {
            if (frequency <= minimumcount) {
                minimumcount = frequency;
                free(wordChosen);
                wordChosen = strdup(word);
                
            }
        }
        currentLinkedList = currentLinkedList->next;
    }
    char firstChar= wordChosen[0];
    count[(firstChar)-'a']--;
    return wordChosen;
}

// Function to display the introduction dialogue
void displayEffect() {
    printf("Stop! Who dares to venture into this land!?\n\n");
    sleep(3);
    printf("Well, well.\n\n");
    sleep(2);
    printf("It seems you are no muggle after all! In that case, allow the Marauders to present: \n\n");
    sleep(3);
    printf("Hogwarts School of Witchcraft and Wizardry!\n\n");
    sleep(3);
    printf("Tonight, the grand hall is filled with an air of anticipation...\n\n");
    sleep(3);
    printf("Students from all four houses have gathered.\n\n");
    sleep(3);
    printf("Even the paintings seem alert.\n\n");
    sleep(2);
    printf(". ");
    sleep(1);
    printf(". ");
    sleep(1);
    printf(". \n");
    sleep(2);
    printf("BOOM!!! *screaming*\n\n");
    sleep(1);
    printf("We are under attack! Darkness approaches, and Grindlewald leads it our way!\n\n");
    sleep(1);
    printf("QUICK! Valiant wizard, tell us what you are called and save us!\n\n");
}

// Function to display the starting dialogue
void displayStart(char name1[], char name2[]) {
    printf("The Grandmaster Dumbledore steps forward and announces:\n\n");
    sleep(3);
    printf(" 'Hogwarts is under attack, and our fate lies in the hands of one wizard alone. . .' \n\n");
    sleep(3);
    printf("'Tonight, we shall witness an epic duel of spells!'\n\n");
    sleep(3);
    printf("%s takes position, ready to cast the first spell...\n\n", name1);
    sleep(3);
    printf("%s prepares to counter...\n\n", name2);
    printf("Wands out... \n\n");
    sleep(3);
    printf("3... \n");
    sleep(3);
    printf("2... \n");
    sleep(2);
    printf("1... \n");
    sleep(1);
    printf("The SpellMaster battle begins now! DUEL!\n\n");
    sleep(2);
}

// Function to check if there exist words in the original list that start with the last letter of the previous word
int wordsStartingWithChar(char *words[], char c, int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        if (c == words[i][0])
            return 1;
    }
    return 0;
}

// Function to convert a string to lowercase
void toLowerCase(char word[]) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// Function to check if a word is found in an array
int isFound(char word[], char *array[], int size) {
    char lowercaseWord[100];
    strcpy(lowercaseWord, word);
    toLowerCase(lowercaseWord);

    for (int i = 0; i < size; i++) {
        if (strcmp(lowercaseWord, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if the first letter of the new word matches the last letter of the old word
int sameLetter(char* oldWord, char* newWord) {
    if (strlen(oldWord) == 0 || strlen(newWord) == 0) {
        return 1;
    }
    char lastChar = oldWord[strlen(oldWord) - 1];
    char firstChar = newWord[0];
    if (firstChar == lastChar)
        return 1;
    return 0;
}

// Function to print an array of words
void printWords(char *words[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        printf("%-20s", words[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}
/*   void insert(char wordToInsert[], wordNode* array[]) 
     requires: a string containing the word to be inserted and array of pointers to Wordnode representing the head nodes of linked list for each character of the alphabet.
     effects:Inserts a new nodeto the  linked list corresponding to the first letter of the word.*/

/*   char* botSpell(wordNode *head, int *count, const char level[], char *array[], int size) 
     requires: a pointer to the head of linked list, array of integers to represent the count of words starting with each 
     letter of the alphabet , a string "level" representing the difficulty level(easy or hard),an array of strings that contains previously chosen words and the size of the array.
     effects: If the level is "easy", Bob picks the word with the maximum frequency from the list, making it easier for the player. 
              If the level is "hard", Bob selects the word with the minimum frequency, reducing the player's options and increasing the challenge.*/
/*   displayEffect();
     requires: nothing 
     effects:print an introductory dialogue with delays between lines.*/

/*   void displayStart(char name1[], char name2[])
     requires:  two strings representing the name of first and second player
     effects:  print a starting dialogue using name of players*/

/*   int wordsStartingWithChar(char *words[], char c, int sizeOfArray) 
     requires:array of strings, the first letter "c" of the word  and the size of the array
      effects: check if there exist words in the original list that start with the character "c"*/

/*   void toLowerCase(char word[]) 
     requires: array of characters(string)
     effects: convert the given string to lowercase*/

 /*int isFound(char word[], char *array[], int size)
 requires: a string word, an array of strings, and its size
 effects: returns 1 if the string word exists in the given array and 0 otherwise */ 

/*int sameLetter(char* oldWord, char* newWord)
 requires: the old chosen word and the newly chosen word
 effects: returns 1 if the last letter of the old word is equal to the first letter of the new word and returns 0 otherwise */

/*void printWords(char *words[], int sizeOfArray)
 requires: an array of strings, and its size
 effects: prints the words of the array in a certain format */
 

   
