#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

typedef struct wordNode {
    char word[50];
    struct wordNode* next;
} wordNode;

int cast_spell_Marauders(char **spells, int num_spells, char *previous_spell, char **used_spells, int num_used_spells) {

    srand(time(NULL));
    int FIRSTminimumcount = INT_MAX;
    int minimumcount = INT_MAX;
    char * word = "";
    char* wordChosen  = spells[0];
    int alphabet = 26;
    int returnIndex = rand() % num_spells;
    int lastLetterCounter[alphabet];
    for (int i = 0; i < alphabet; i++) {
        lastLetterCounter[i] = 0;
    }
    wordNode* letteredwords[alphabet];
    for (int i = 0; i < alphabet; i++) {
        letteredwords[i] = NULL;
    }
    for (int i = 0; i < num_spells; i++) {
        if (!isFound(spells[i], used_spells, num_used_spells)) {
            int indexOfLetter = spells[i][0] - 'a';
            lastLetterCounter[indexOfLetter]++;
            insert(spells[i], letteredwords);
        }  
    }
    if (num_used_spells == 0) {
        for (int i = 0; i < num_spells; i++) {
            int lastLetterIDX = spells[i][strlen(spells[i]) - 1] - 'a';
            if (lastLetterCounter[lastLetterIDX] <= FIRSTminimumcount) {
                returnIndex = i;
                FIRSTminimumcount = lastLetterCounter[lastLetterIDX];
            }
        }
        return returnIndex;
    }
    int letterIndexForList = previous_spell[strlen(previous_spell) - 1];
    wordNode* currentLinkedList = letteredwords[previous_spell[letterIndexForList] - 'a'];
    while (currentLinkedList != NULL) {
        char *word = currentLinkedList->word;
        
        if (!isFound(word, used_spells, num_used_spells)) { 
            char lastLetter = tolower(word[strlen(word) - 1]);
            int frequency = lastLetterCounter[lastLetter - 'a'];
            if (frequency <= minimumcount) {
                minimumcount = frequency;
                free(wordChosen);
                wordChosen = strdup(word);
            }
        }
        currentLinkedList = currentLinkedList->next;
    }
    for (int i = 0; i < num_spells; i++) {
        if (strcmp(spells[i], wordChosen) == 0) {
            returnIndex  = i;
        }
    }
    return returnIndex;
}
int isFound(char word[], char *array[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(word, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
void insert(char wordToInsert[], wordNode* array[]) {
    int index = tolower(wordToInsert[0]) - 'a'; // we subtract 'a' since we are using ASCII codes
    wordNode* newNode = malloc(sizeof(wordNode));
    strcpy(newNode->word, wordToInsert);
    newNode->next = array[index];
    array[index] = newNode;
}
