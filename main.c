#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *file;
    int wordCount;
    char fileName[] = "spells.txt";
    displayEffect();
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
    
    int random = rand() % 2;   // toss the coin 
 printf("The fates have conspired, the wands have been chosen, and now, it's time to decide who will cast the first spell...\n");
    printf("\n %d",random);
    if (random == 0) {
        printf("By the powers of the Elder Wand, Player 1 shall commence this duel!\n");
    } else {
        printf("By the grace of Merlin's beard, Player 2 shall kick things off!\n");
}
}
void displayEffect() {

    printf("Welcome to Hogwarts School of Witchcraft and Wizardry!\n");
    sleep(1);
    printf("Tonight, the grand hall is filled with an air of anticipation...\n");
    sleep(1);
    printf("Students from all four houses have gathered.\n");
    sleep(1);
    printf("Even the paintings seem alert.\n");
    sleep(2);
    printf("The Grandmaster Dumbledore steps forward and announces:\n");
    sleep(2);
    printf("'Tonight, we shall witness a duel of spells!'\n");
    sleep(2);
    printf("Harry Potter takes his position...\n");
    sleep(1);
    printf("Wands out... \n");
    sleep(1);
    printf("3... \n");
    sleep(1);
    printf("2... \n");
    sleep(1);
    printf("1... \n");
    sleep(1);
    printf("DUEL!\n\n");
    sleep(1);
    printf("The Spell Master competition begins now!\n\n");
    sleep(1);
    char previousSpell[100] = "";
    char chosenSpell[100];

    while (1) {
        printf("%s, choose your spell: ", currentPlayer);
        scanf("%s", chosenSpell);

        if (!isFound(chosenSpell, words, wordCount)) {
            printf("%s wins! The spell is not in the list.\n", nextPlayer);
            break;
        }

        if (!sameLetter(previousSpell, chosenSpell) && strlen(previousSpell) != 0) {
            printf("%s wins! Spell does not match the last letter of the previous spell.\n", nextPlayer);
            break;
        }

        strcpy(previousSpell, chosenSpell);

        char temp[50];
        strcpy(temp, currentPlayer);
        strcpy(currentPlayer, nextPlayer);
        strcpy(nextPlayer, temp);
    }

    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}
}
