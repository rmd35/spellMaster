/*
excerpt of main code, meant to create an array of linked lists, would a 2d array be better?
*/
typedef struct wordNode wordNode;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

struct wordNode {
    char word[50];
    struct wordNode* next;
};
void printCharCount(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c = %d\n", (i + 97), arr[i]);
    }
}
//////// NEW ADDITION
void insert(char wordToInsert[], wordNode* array[]) {
    int index = wordToInsert[0] - 97;
    wordNode* newNode = malloc(sizeof(struct wordNode));
    strcpy(newNode->word, wordToInsert);
    newNode->next = array[index];
    array[index] = newNode;
}

void printLinkedList(wordNode* array[], int index) {
    wordNode *current_node = array[index];
   	while ( current_node != NULL) {
        printf("%d ", current_node->word);
        current_node = current_node->next;
    }

}
//////////////////////////////
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
    wordNode* words[alphabet];
    for (int i = 0; i < alphabet; i++) {
        words[i]  = malloc(sizeof(struct wordNode));
    }

    for (int i = 0; i < wordCount; i++) {
        char word[100];
        if (fscanf(file, "%s", word) != 1) {
            printf("Is this an old book? I cannot read this!\n");
            fclose(file);
            free(words);
            return 0;
        }
        tolower(word); 
        words[i] = strdup(word);
        //allocates memory and copies the word into it

        int toGetIndex = 97;
        int indexOfLetter = word[0] - toGetIndex;
        lastLetterCounter[indexOfLetter]++;
        //we increment the array of letter counters to find how many of each letter we've got.

    }
    fclose(file); //now that we finished copying the words, we can close the file and use the array.
    //printCharCount(lastLetterCounter, 26);
    printLinkedList(words, 16);
}
