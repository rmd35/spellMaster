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
int main() {
    char *spells1[] = {"abra", "alohomora", "accio", "expelliarmus", "wingardiumleviosa"};
    char *used_spells1[] = {"abra", "accio"};
    char previous_spell1[] = "accio";

    int num_spells1 = sizeof(spells1) / sizeof(spells1[0]);
    int num_used_spells1 = sizeof(used_spells1) / sizeof(used_spells1[0]);

    int spellIndex1 = cast_spell_Marauders(spells1, num_spells1, previous_spell1, used_spells1, num_used_spells1);

    printf("Chosen spell: %s\n", spells1[spellIndex1]);
    printf("--------------------------------------------\n");

    // Test Case 2
    char *spells2[] = {"expelliarmus", "engorgio", "expecto_patronum", "alohomora", "accio", "wingardiumleviosa"};
    char *used_spells2[] = {"expelliarmus", "accio", "wingardiumleviosa"};
    char previous_spell2[] = "wingardiumleviosa";

    int num_spells2 = sizeof(spells2) / sizeof(spells2[0]);
    int num_used_spells2 = sizeof(used_spells2) / sizeof(used_spells2[0]);

    int spellIndex2 = cast_spell_Marauders(spells2, num_spells2, previous_spell2, used_spells2, num_used_spells2);

    printf("Chosen spell: %s\n", spells2[spellIndex2]);
    printf("--------------------------------------------\n");

    // Test Case 3 (Larger dataset)
    char *large_spells[] = {
        "accio", "alohomora", "avada_kedavra", "alarte_ascendare", "aguamenti", "brackium_emendo", "colloportus", 
        "defodio", "expelliarmus", "expecto_patronum", "engorgio", "evanesco", "ferula", "geminio", "impedimenta",
        "incendio", "lumos", "nox", "obliviate", "protego", "reducio", "reparo", "riddikulus", "serpensortia",
        "stupefy", "tarantallegra", "wingardiumleviosa", "sectumsempra", "muffliato", "legilimens", "imperio"
    };
    char *large_used_spells[] = {"expelliarmus", "lumos", "reparo", "alohomora", "accio"};
    char large_previous_spell[] = "accio";

    int num_large_spells = sizeof(large_spells) / sizeof(large_spells[0]);
    int num_large_used_spells = sizeof(large_used_spells) / sizeof(large_used_spells[0]);

    int spellIndex_large = cast_spell_Marauders(large_spells, num_large_spells, large_previous_spell, large_used_spells, num_large_used_spells);

    printf("Chosen spell: %s\n", large_spells[spellIndex_large]);

    return 0;
}
