///////////////////// SPELLMASTER PHASE 2 /////////////////////

///////////////////// THE MARAUDERS GROUP /////////////////////

///// ROLA DINNAWI, JULIA DIRAWI, MONA JAMAL //////////////////

/*
********Report on the SpellMaster Duel Game***********:

*********Overview***********:

The SpellMaster Duel game is a text-based game implemented in C, simulating a magical duel between a player and a computer-controlled opponent named Grindlewald. 
The players take turns casting spells by choosing words from the provided list of spells 'spells.txt' file. The rules of the games lie in choosing a spell that 
must be more powerful than the previous one and should satisfy conditions related to uniqueness and starting/ending characters. The game starts by prompting the 
human player for their name and displaying the list of available spells. A fair coin toss determines the starting player, and the program proceeds to alternate 
between the human player and the bot, asking for their moves in each turn. The bot's move is generated based on the same rules as the human player. If a move 
results in a winner, the program announces the winner and the reason for their victory.



*************Structure and Design**************:

1.File Reading:

The game starts by reading spell data from a file named "spells.txt." The file is expected to contain the number 
of spells and a list of words. The spells are stored in an array, and additional data structures are initialized 
to keep track of spell frequencies and organize them alphabetically in linked lists.

2. Data Structures:

a. wordNode Structure:
  - Represents a node in a linked list for each starting letter.
  - Contains a string word and a pointer to the next node.
  
b. Arrays and Counters:
  - Arrays are used to store spell data, and counters to keep track of the frequency of words starting with each letter.

3. Game Initialization:

Players are prompted to enter their wizard name and choose the difficulty level (easy or hard). 
The game randomly selects a starting player and announces the beginning of the duel.

4. Game Loop:

The game proceeds with a do-while loop where players and Grindlewald take turns casting spells. 
The players input their spells, while Grindlewald's spell selection is automated based on the chosen difficulty level. 
The game checks the validity of each move, including word existence, starting letter matches, and uniqueness.

5. Game Over:

The game ends when a player makes an invalid move or runs out of spells. 
The winner or loser is determined based on the last valid move made.

6. Functions:

a. insert:
   - Inserts a word into the appropriate linked list based on its starting letter.

b. botSpell:
   - Chooses Grindlewald's spell based on difficulty level and letter frequency.

c. displayEffect:
   - Displays an introductory dialogue for the magical duel.

d. displayStart:
   - Announces the start of the duel, introducing the player and Grindlewald.

e. wordsStartingWithChar:
   - Checks if there are words in the spellbook starting with a given character.

f. toLowerCase:
   - Converts a string to lowercase.

g. isFound:
   - Checks if a word is found in an array or not.

h. sameLetter:
   - Checks if the first letter of a new spell matches the last letter of the previous spell.

i. printWords:
   - Prints an array of strings, displaying available spells.
   

7.Code Documentation:
The codebase includes comments that detail functionality at both the micro and macro levels.
Above each function, there is the purpose of the code, its expected input, and output. For example,
the "botspell" function includes explanation of the decision making process of Bob based on difficulty level.

8.Challenges faced:
During devolopment,managing dynamic memory allocations and mastering C syntax posed challenges.The game required 
efficient memory management to prevent leaks due to its extensive spell list. Additionally, C syntax demanded 
precise attention , especially with pointers and memory addresses.
9. Testing:
Unit testings were written for each function to validate their correctness in isolation. Then, integration tests were performed to
ensure that the entire  code functions properly.

***Conclusion***:

The SpellMaster Duel game code provides an engaging and unique gaming experience.
The strategic use of words and the implementation of the magical duel concept make this code an interesting and creative project.*/

