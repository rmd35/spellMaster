#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

///////////////functions///////////////

//dialogue: introduction
void displayEffect() {
    printf("Stop! Who dares to venture into this land!?\n");
    sleep(3);
    printf("Well, well.\n");
    sleep(2);
    printf("It seems you are no muggle after all! In that case, allow the Marauders to present: \n");
    sleep(3);
    printf("Hogwarts School of Witchcraft and Wizardry!\n");
    sleep(3);
    printf("Tonight, the grand hall is filled with an air of anticipation...\n");
    sleep(3);
    printf("Students from all four houses have gathered.\n");
    sleep(3);
    printf("Even the paintings seem alert.\n");   
}
//dialogue: announcing who begins
void displayStart(char name1[], char name2[]) {
    printf("The Grandmaster Dumbledore steps forward and announces:\n\n");
    sleep(3);
    printf("'Tonight, we shall witness a duel of spells!'\n\n");
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
    printf("The Spell Master competition begins now! DUEL!\n\n");
    sleep(2);
}

//checks if there exists words in the og list that start with last letter of previous word
int wordsStartingWithChar(char *words[], char c, int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        if (c == words[i][0])
            return 1;
    }
    return 0;
}

//converts to lowercase to tackle all possible ways a spell is written
void toLowerCase(char word[]) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

//searches an array to check whether a word is found in it. We use this in the original 
//list, and already-used words list
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

//checks if the first letter of the new word matches the last letter of the old word
int sameLetter(char* oldWord, char* newWord){
    if(strlen(oldWord)==0 || strlen(newWord)==0){
        return 1;
    }    
    char lastChar= oldWord[strlen(oldWord)-1];
    char firstchar= newWord[0];
    if(firstchar==lastChar)
        return 1;
    return 0;
}

//print method that prints an array
void printWords(char *words[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
         printf("%-20s", words[i]);
        if ((i + 1) % 5 == 0){
            printf("\n");
        }
    }
    printf("\n\n");
}


//////////////////////      MAIN        /////////////////

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

    for (int i = 0; i < wordCount; i++) {
        char word[100];
        if (fscanf(file, "%s", word) != 1) {
            printf("Is this an old book? I cannot read this!\n");
            fclose(file);
            free(words);
            return 0;
        }
         toLowerCase(word); 
        words[i] = strdup(word);
        //allocates memory and copies the word into it
    }
    fclose(file); //now that we finished copying the words, we can close the file and use the array.

/////////////////////       END OF FILE READING     ///////////////////////

/////////////////////         BEGIN THE GAME        ///////////////////////

    displayEffect();

    printf("Powerful wizards who ventured thus far, tell us what you are called! \n");
    char player1[50];
    char player2[50];
    scanf("%s", player1);
    scanf("%s", player2);

    srand(time(NULL));
    int random = rand() % 2;   // toss the coin 
    printf("The fates have conspired, the wands have been chosen, and now, it's time to decide who will cast the first spell...\n\n");
    sleep(2);
    printf("let us toss a galleon and see who the laws of arithmancy favor!\n\n");
    sleep(2);

    char Playing[50]; // contains the name of whoever is playing

    if (random == 0) {
        printf("By the powers of the Elder Wand, %s shall commence this duel!\n\n", player1);
        displayStart(player1,player2);
        strcpy(Playing, player1);
    } else {
        printf("By the grace of Merlin's beard, %s shall kick things off!\n\n", player2); 
        displayStart(player2,player1);
        strcpy(Playing, player2);
    }

    // creating an array that stores the words chosen
    char **chosenWords = (char **)malloc(wordCount * sizeof(char *));
    if (chosenWords == NULL) {
        printf("Memory allocation error for chosenWords\n");
        free(chosenWords); // in case the array is full, clean up previous memory allocation
        return 1;
    }

    int turnCount = 0;
    printWords(words, wordCount);
    char retaliate[80];
    
    //do-while to keep the game running until someone loses.
    do {
        printf("What is your next move?\n");
        scanf("%s", retaliate);
        toLowerCase(retaliate);
        chosenWords[turnCount] = (char *)malloc((strlen(retaliate) + 1) * sizeof(char));

        if (chosenWords[turnCount] == NULL) {
            printf("No space for such spell!\n");
            // clean up memory and exit
            for (int i = 0; i < turnCount; i++) {
                free(chosenWords[i]);
            }
            free(chosenWords);
            free(words);
            return 1;
        }

        strcpy(chosenWords[turnCount], retaliate);
        printf("%s casted this spell: %s\n", Playing, retaliate);
        chosenWords[turnCount] = strdup(retaliate);
        turnCount++;

        if (!isFound(retaliate, words, wordCount) || !wordsStartingWithChar(words, retaliate[strlen(retaliate) - 1], wordCount) || 
        (turnCount >= 2 && !sameLetter(chosenWords[turnCount - 2], retaliate)) || isFound(retaliate, chosenWords, turnCount - 1)) {
            break;
        }

    // switch turns only if the current player made a valid move
        if (strcmp(Playing, player1) == 0)
            strcpy(Playing, player2);
        else 
            strcpy(Playing, player1);

    } while (1);  

/////////////////////////       GAME OVER       /////////////////////////

    // now we announce who the loser is and the condition that broke loop
    if (isFound(retaliate, chosenWords, turnCount - 1) == 1)
        printf("Such lack of creativity! This spell has been used! %s loses!", Playing);
    else if (isFound(retaliate, words, wordCount) == 0)
        printf("%s casts a spell unknown! Such a wonky move! %s loses!", Playing, Playing);
    else if (wordsStartingWithChar(words, retaliate[strlen(retaliate) - 1], wordCount) == 0) {
        if (strcmp(Playing, player1) == 0)
            strcpy(Playing, player2);
        else
            strcpy(Playing, player1);
        printf("it seems the odds were against you, %s. The english lexicon has betrayed thee.", Playing);
    }
    else if (sameLetter(chosenWords[turnCount - 2], retaliate) == 0)
        printf("%s offend the laws of the duel! The letters match not! Read for Merlin and Morgana's sake!", Playing);
    
    //free up memory
    for (int i = 0; i < turnCount; i++) {
        free(chosenWords[i]);
    }
    free(chosenWords);
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
}
