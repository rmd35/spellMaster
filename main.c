typedef struct wordNode wordNode;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

struct wordNode {
    char word[50];
    struct wordNode* next;
};

//////// NEW ADDITION
void insert(char wordToInsert[], wordNode* array[]) {
    int index = wordToInsert[0] - 'a';
    wordNode* newNode = malloc(sizeof(struct wordNode));
    strcpy(newNode->word, wordToInsert);
    newNode->next = array[index];
    array[index] = newNode;
}
//////////////////////////////

//min & max function
char* botSpell(wordNode *head, int *count, const char level[]) {
    int maximumcount = 0;
    int minimumcount = INT_MAX; // Set to maximum possible value
    char *wordChosen = NULL;
    wordNode *currentLinkedList = head;
        while(currentLinkedList != NULL){
            char *word = currentLinkedList->word; // Assuming the Node has a data member that is a string
            char lastLetter = tolower(word[strlen(word) - 1]); // Ensure lowercase
            int frequency = count[lastLetter - 'a'];

            if ( strcmp(level, "easy") == 0) {
                if (frequency >= maximumcount) {
                    maximumcount = frequency;
                    wordChosen = strdup(word);
                }
            } else if ( strcmp(level, "hard") == 0)
            {
                if (frequency <= minimumcount) {
                    minimumcount = frequency;
                    wordChosen = strdup(word);
                }
            }
            currentLinkedList = currentLinkedList->next;
    }

    return wordChosen;
}
//////////////////////////

int main() {
FILE *file;
    int wordCount;
    char fileName[] = "spells.txt";
    file = fopen(fileName, "r"); //reading the file
    
    // alerts you if the file is empty
    if (file == NULL) {
        printf("Strange, your spellbook is missing! \n"); 
        return 0;
    }

    // if we get past the if-statement then our file is found and we can start reading
    if (fscanf(file, "%d", &wordCount) != 1) {
        // in this case, we say != 1 not to indicate that we have 1 word, here 1 acts as a boolean
        //this condition ensures that we read an integer in the file 
    }
    char **words = (char **)malloc(wordCount * sizeof(char *));
    if (words == NULL) {
        printf("Your bookshelf is full of knick-knacks and rubbish, free up space!\n");
        fclose(file);
        return 0;
    }
    // if we get past the if statement, then the memory allocation was successful

    int alphabet = 26;
    int lastLetterCounter [alphabet];
    for (int i = 0; i < alphabet; i++) {
        lastLetterCounter[i] = 0;
    }
    wordNode* letteredwords[alphabet];
    for (int i = 0; i < alphabet; i++) {
        letteredwords[i] = NULL;
    }

    for (int i = 0; i < wordCount; i++) {
        char word[100];
        if (fscanf(file, "%s", word) != 1) {
            printf("Is this an old book? I cannot read this!\n");
            fclose(file);
            free(words);
            return 0;
        }
        words[i] = strdup(word); //allocates memory and copies the word into it
        int indexOfLetter = word[0] - 'a';
        lastLetterCounter[indexOfLetter]++;
        insert(word, letteredwords); //we increment the array of letter counters to find how many of each letter we've got.
    }

    char* result = botSpell(letteredwords[15], lastLetterCounter, "hard");
    if (result == NULL) {
        printf("Error: Memory allocation failed for ourfinalWord\n");
        return 1;  // Indicate an error
    }
    printf("%s\n", result); // Print the chosen word

    for (int i = 0; i < alphabet; i++) { // Free memory
    wordNode* current_node = letteredwords[i];
    while (current_node != NULL) {
        wordNode* temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
}

    fclose(file);
   
}
