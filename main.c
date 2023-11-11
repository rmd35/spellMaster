///////////////////// SPELLMASTER PHASE 2 /////////////////////

///////////////////// THE MARAUDERS GROUP /////////////////////

///// ROLA DINNAWI, JULIA DIRAWI, MONA JAMAL //////////////////

///////////////////// headers /////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

// structure node for the linked list
typedef struct wordNode {
    char word[50];
    struct wordNode* next;
} wordNode;

/////////////// function declarations /////////////////////

void insert(char wordToInsert[], wordNode* array[]);
char* botSpell(wordNode *head, int *count, const char level[], char *array[], int size);
void displayEffect();
void displayStart(char name1[], char name2[]);
int wordsStartingWithChar(char *words[], char c, int sizeOfArray);
void toLowerCase(char word[]);
int isFound(char word[], char *array[], int size);
int sameLetter(char* oldWord, char* newWord);
void printWords(char *words[], int sizeOfArray);


////////////////////////// MAIN /////////////////////////

int main() {

    ///////////////////// FILE READING //////////////////

    FILE *file;
    int wordCount;
    char fileName[] = "spells.txt";
    file = fopen(fileName, "r"); // reading the file

    // checking if the file is empty
    if (file == NULL) {
        printf("Strange, your spellbook is missing! \n");
        return 0;
    }

    // reads the number of words from the file
    if (fscanf(file, "%d", &wordCount) != 1) {
        printf("How many spells are in this book!? The index is missing! \n");
        fclose(file);
        return 0;
    }

    // allocate memory and store words in words
    char **spells = (char **)malloc(wordCount * sizeof(char *));
    if (spells == NULL) {
        printf("Your shelf is filled with trinkets and\n");
        fclose(file);
        return 0;
    }

    // initialize array that has counters for each starting letter
    int alphabet = 26;
    int lastLetterCounter[alphabet];
    for (int i = 0; i < alphabet; i++) {
        lastLetterCounter[i] = 0;
    }

    // initialize array of linked lists for each letter
    wordNode* letteredwords[alphabet];
    for (int i = 0; i < alphabet; i++) {
        letteredwords[i] = NULL;
    }

    // read words from file and fill the arrays
    for (int i = 0; i < wordCount; i++) {
        char word[100];
        if (fscanf(file, "%s", word) != 1) {
            printf("I cannot read this! It is gibberish!\n");
            fclose(file);
            free(spells);
            return 0;
        }

        toLowerCase(word);
        spells[i] = strdup(word);

        // in addition to storing in an array, increment the letter counter, and insert the word in the correct linked list
        int indexOfLetter = word[0] - 'a';
        lastLetterCounter[indexOfLetter]++;
        insert(word, letteredwords);
    }
    fclose(file); // close the file after reading

///////////////////// FILE READING DONE //////////////////


///////////////////// BEGIN THE GAME /////////////////////

    // dialogue
    displayEffect();

    // names of players and level
    char player1[50];
    char player2[] = "Grindlewald"; // villain!
    char level[10];

    // takes name from the user, and difficulty they want to play
    printf("Enter your wizard name: ");
    scanf("%s", player1);
    printf("\n\n");
    printf("How difficult would you like the game to be? (easy/hard): ");
    scanf("%s", level);

    srand(time(NULL));
    int random = rand() % 2; // toss the galleon

    printf("The fates have conspired, the wands have been chosen, and now, it's time to decide who will cast the first spell...\n\n");
    sleep(2);
    printf("Let us toss a galleon and see whom the laws of arithmancy favor!\n\n");
    sleep(2);

    char Playing[50]; // contains the name of whoever is currently playing

    // sets Playing to the starting player based on the random result
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

    // create an array that stores the words chosen
    char **usedSpells = (char **)malloc(wordCount * sizeof(char *));
    if (usedSpells == NULL) {
        printf("Where do I write all these spells I casted?\n");
        for (int i = 0; i < wordCount; i++) {
            free(usedSpells[i]);
        }
        free(usedSpells); // cleans up previous memory allocation
        return 1;
    }
    for (int i = 0; i < wordCount; i++) {
        usedSpells[i] = NULL;
    }

    int turnCount = 0; // keeps track of count and where in usedSpells we will add the spell
    printWords(spells, wordCount);
    char retaliate[80];

    // do-while loop, keeps the game running until someone loses
    do {
        printf("What is your next move?\n");
        if (random != 0) { // in case bot was chosen to start, it will choose a word at random
            int randomIndex = rand() % wordCount;
            strcpy(retaliate, spells[randomIndex]);
            random = 0; // ensures we will not enter this if-statement anymore
        } else {
            if (strcmp(Playing, player1) == 0) {
                scanf("%s", retaliate);
            } else {
                char lastLetter = retaliate[strlen(retaliate) - 1];
                strcpy(retaliate, botSpell(letteredwords[lastLetter - 'a'], lastLetterCounter, level, usedSpells, turnCount));
            }
        }
        toLowerCase(retaliate); // ensures that we tackle all cases the word is written

        if (usedSpells[turnCount] != NULL) {
            // clean up memory and exit
            for (int i = 0; i < turnCount; i++) {
                free(usedSpells[i]);
            }
            free(usedSpells);
            free(spells);
            return 1;
        }
        if (turnCount >= wordCount) { // ensures that the game will exit once the turns exceed the number of words we have
            printf("You are spewing nonsense! You've no more cards to deal!\n");
            break;
        }
        printf("%s casted this spell: %s\n", Playing, retaliate);
        usedSpells[turnCount] = strdup(retaliate);
        turnCount++;

        if (!isFound(retaliate, spells, wordCount) || !wordsStartingWithChar(spells, retaliate[strlen(retaliate) - 1], wordCount) ||
            (turnCount >= 2 && !sameLetter(usedSpells[turnCount - 2], retaliate)) || isFound(retaliate, usedSpells, turnCount - 1)) {
            break;
        }

        // switch turns only if the current player made a valid move
        if (strcmp(Playing, player1) == 0)
            strcpy(Playing, player2);
        else
            strcpy(Playing, player1);

    } while (1);

    /////////////////////// GAME OVER ///////////////////////

    // now we announce who the loser is and why they lost
    if (isFound(retaliate, usedSpells, turnCount - 1) == 1)
        printf("Such lack of creativity! This spell has been used! %s loses!\n", Playing);

    else if (isFound(retaliate, spells, wordCount) == 0)
        printf("%s casts a spell unknown! Such a wonky move! %s loses!\n", Playing, Playing);

    // in this case we switch the name again since the loser is not the one who cast a spell
    else if (wordsStartingWithChar(spells, retaliate[strlen(retaliate) - 1], wordCount) == 0) {
        if (strcmp(Playing, player1) == 0)
            strcpy(Playing, player2);
        else
            strcpy(Playing, player1);
        printf("It seems the odds were against you, %s. The English lexicon has betrayed thee.\n", Playing);
    } 
    
    else if (sameLetter(usedSpells[turnCount - 2], retaliate) == 0)
        printf("%s offends the laws of the duel! The letters match not! Read for Merlin and Morgana's sake!\n", Playing);

    // free up memory
    for (int i = 0; i < turnCount; i++) {
        free(usedSpells[i]);
    }
    free(usedSpells);

    for (int i = 0; i < wordCount; i++) {
        free(spells[i]);
    }
    free(spells);

    return 0;
}

/////////////////// FUNCTIONS IMPLEMENTATIONS ////////////////////

// function to insert a word into a linked list
void insert(char wordToInsert[], wordNode* array[]) {
    int index = wordToInsert[0] - 'a'; // we subtract 'a' since we are using ASCII codes
    wordNode* newNode = malloc(sizeof(wordNode));
    strcpy(newNode->word, wordToInsert);
    newNode->next = array[index];
    array[index] = newNode;
}

// function that chooses a spell based on difficulty level
char* botSpell(wordNode *head, int *count, const char level[], char *array[], int size) {
    int maximumcount = 0; // set to minimum value, which is 0 since we initialized the count array to 0
    int minimumcount = INT_MAX; // set to maximum possible value
    char *wordChosen = NULL;
    wordNode *currentLinkedList = head;

    while (currentLinkedList != NULL) {
        char *word = currentLinkedList->word;
        
        if(!isFound(word, array, size)) {  // ensures that the word we choose is not already chosen, we will not reach a case where wordChosen remains null
            char lastLetter = tolower(word[strlen(word) - 1]);
            int frequency = count[lastLetter - 'a'];
            // easy level: chooses word whose last letter has the most options for the user to choose from
            if (strcmp(level, "easy") == 0) {
                if (frequency >= maximumcount) {
                    maximumcount = frequency;
                    free(wordChosen);
                    wordChosen = strdup(word);
                }
            } 
            // hard level: chooses word whose last letter has the least options for the user to choose from
            else if (strcmp(level, "hard") == 0) {
                if (frequency <= minimumcount) {
                    minimumcount = frequency;
                    free(wordChosen);
                    wordChosen = strdup(word);
                }
            }
        }
        currentLinkedList = currentLinkedList->next;
    }
    // decrement the counter in the letters array 
    if (wordChosen != NULL) {
        char firstChar= wordChosen[0];
        count[(firstChar)-'a']--;
    }
    
    return wordChosen;
}

// dialogue: introduction
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
    printf(". \n\n");
    sleep(2);
    printf("BOOM!!! *screaming*\n\n");
    sleep(1);
    printf("We are under attack! Darkness approaches, and Grindlewald leads it our way!\n\n");
    sleep(1);
    printf("QUICK! Valiant wizard, tell us what you are called and save us!\n\n");
}

// dialogue: announces beginning of duel, using the names in the correct spots to announce who begins as well
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

// function that checks if there are words in the spells list that start with the last letter of the previous word
int wordsStartingWithChar(char *words[], char c, int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        if (c == words[i][0])
            return 1;
    }
    return 0;
}

// function that converts a string to lowercase
void toLowerCase(char word[]) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// function to check if a string is found in an array
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

// function to check if the first letter of the new spell matches the last letter of the previous spell
int sameLetter(char* oldWord, char* newWord) {
    if (strlen(oldWord) == 0 || strlen(newWord) == 0) {
        return 1;
    }
    char lastChar = oldWord[strlen(oldWord) - 1];
    char firstChar = newWord[0];
    if (firstChar == lastChar) {
        return 1;
    }
    return 0;
}

// function to print an array of strings
void printWords(char *words[], int sizeOfArray) {
    for (int i = 0; i < sizeOfArray; i++) {
        printf("%-20s", words[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}
