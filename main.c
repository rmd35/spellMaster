#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int isFound(const char *word, const char *array[], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(word, array[i]) == 0) {
            // Word found in the array
            return 1;
        }
    }
    // Word not found in the array
    return 0;
}

 int sameLetter(char* oldWord, char* newWord){
    if(strlen(oldWord)==0 || strlen(newWord)==0){
        return 0;
}
char lastChar= oldWord[strlen(oldWord)-1];
char firstchar= newWord[0];
if(firstchar==lastChar){
    return 1;
}
return 0;
}
int main() {
    FILE *file;
    int wordCount;
    char fileName[] = "spells.txt";
    file = fopen(fileName, "r"); //reading the file

    if (file == NULL) {
        printf("Strange, your spellbook is missing! \n"); // alerts you if the file is empty
        return 0;
    }

    // if we get past the if-statement then our file is found and we can start reading
    if (fscanf(file, "%d", &wordCount) != 1) {
        // in this case, we say != 1 not to indicate that we have 1 word, here 1 acts as a boolean
        //this condition ensures that we read an integer in the file 
    }
    char **words = (char **)malloc(wordCount * sizeof(char *));
    if (words == NULL) {
        printf("Your bookshelf is full of knick-knacks and rubbish, free up space!");
        fclose(file);
        return 0;
    }
    // if we get past the if statement, then the memory allocation was successful

    for (int i = 0; i < wordCount; i++) {
        char word[100];
        if (fscanf(file, "%s", word) != 1) {
            printf("Is this an old book? I cannot read this!");
            fclose(file);
            free(words);
            return 0;
        }
        words[i] = strdup(word);
        //allocates memory and copies the word into it
    }

    fclose(file); //now that we finished copying the words, we can close the file and use the array.
    
    printf("Who dares to venture into this land!?");
    printf("Well, well. It seems you are no muggle after all!");
    
    
}
