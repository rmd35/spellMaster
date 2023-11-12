1. Title
  - Project Name: SpellMaster
  - Date: November 12th, 2023
  - Authors: Rola Dinnawi, Julia Dirawi, Mona Jamal.

2. Introduction
  - SpellMaster is a fantasy, dialogue-based game which simulates a magical duel between a player and an automated opponent, Grindlewald. The players take turns 
    casting spells by choosing words from the provided list of spells. The rules of the game assert that one should cast a stronger spell than the one preceeding, 
    and the strength of a spell is determined by a set of conditions related to the uniqueness of the word, and the matching of the first letter of a spell to the
    last letter of the word preceding it. The game starts by prompting the client for their name and displaying the list of available spells. A fair coin toss 
    determines the starting player, and the program proceeds to alternate between the client and the bot, asking for their moves in each turn. The bot's 
    move is generated based on the same rules as the human player. If a move results in a loser, the program announces the loser and the reason for their loss.
  - In this report, we will describe the methodology, structure, and more.

3. Objectives
  - Defeat the bot, Grindlewald, who is the villain.
  - Learn and adapt while playing, to overcome the challenges thrown by the bot.

4. Scope
  - The program aims to provide a pleasant and thrilling game experience to the client, according to the difficulty level they choose.
  - The program runs properly if the file to be read follows the format required by the program.
  - The program runs properly if the difficulty level chosen is inserted by the user correctly.
  - Accidentally providing an incorrect writing of a word during the game will count as a loss.
  - The program includes conditions on the words chosen to determine whether the client or bot made valid moves, in the case that one does not,
    the game stops and the loser is announced. Otherwise, it continues running until someone inevitably loses.

5. Methodology
  - In this implementation of SpellMaster, we make use of arrays and linked lists. First, the file is read and stored in an array that will be displayed
    to the client, and while it is being read, we add each word to its corresponding linked list in an array of linked lists. We find the correct index to
    insert the new word in by direct addressing, which takes up O(1) time, rather than O(n) from iterating over the entire array. Then we create an array to 
    store the words used and we keep track of the turns, which will be used later on in the conditions. Additionally, we have an array that counts the words
    starting with each letter; This acts as the basis for implementing two difficulty levels for the client to choose from. 
  - We started by listing what our program already has from the previous phase, and brainstormed what it still needed. It needed the array of counters, the array
    of linked lists, a node structure, and a function for bot to choose a word to return.
  - After that, we decided to implement levels, and we did that by using the array of counters. In the "easy" difficulty level, the bot returned a word starting
    with the last letter of the previous word, and its last letter has the most words left in the words list- we find that using the array of counters - which
    provides the client with more words to choose from. In the "hard" difficulty level, the bot returned a word starting with the last letter of the previous word,
    and its last letter has the least words left in the words list- we find that using the array of counters - which provides the client with less words to choose 
    from. However, the bot does not return an already chosen word.
  - We divided the program's implementation requirements into smaller tasks and tackled each part on its own, handling bugs and memory errors and testing multiple
    cases, before grouping them together. This minimized the errors we encountered, and it was easier to find where the errors were stemming from.
  - Using Github, we presented our codes to each other and reviewed them and edited them.
  - What we learned throughout the duration of this project is the importance of clear communication with your team, and how to efficiently split the work amongst
    ourselves such that each person focuses on a certain part of the project. We are now also more familiar with using Github. 

6. Technologies Used:
  - This program is written in C, and tested on Visual Studio Code. We used multiple libraries based on the program's requirements:
    i.   <stdio.h>: for functions such as printf and scanf.
    ii.  <stdlib.h>: for functions such as memory allocation and deallocation, as well as rand.
    iii. <string.h>: for functions for string manipulation, such as strcpy, strcmp and strlen.
    iv.  <time.h>: for functions that work with time, such as sleep().
    v.   <ctype.h>: for functions for characters such as tolower.
    vi.  <limits.h>: defines various variables, such as INT_MAX.

7. Architecture:
    i. File Reading and Game Set up
        - The program reads data from the file "spells.txt" and initializes the game data appropriately.
        - The program manages the client's input (name, difficulty) and who begins.

    ii. Data Structures
          a. Linked Lists
              - Made up of wordNodes, and it is responsible for storing, inserting, and retrieving words.
              - Arranged alphabetically for more optimized access.
  
          b. Arrays
              - Used to store game data, such as words, linked lists, and counters.

    iii. Game Initialization
        - Player is prompted to enter their wizard name and choose the difficulty level (easy or hard). The game randomly selects a starting 
          player and announces the beginning of the duel.

    iv. Game Loop
        - Iterative. The players take turns casting spells according to the conditions of the game.
        - Keeps track of the spell history, and checks whether the current player made a valid move.

    v. Game Termination
        - One of the conditions is broken. The game terminates and the program announces who lost and why they lost.

    vi. Memory Management
        - Allocate memory for new data structures and types, and deallocate the memory at the end of the program.

    vii. External Interface
        - Usage of an external file "Spells.txt"

    viii. Interaction Between Components
        - The linked list makes use of the wordNode structure, the array of linked lists uses the linked lists. 
        - The function calls utilize all data structures and types used.

    ix. Data Flow
        - The data is first obtained from an external file and allocated in the program's memory, and it is later stored in data structures. 

8. Code Structure
  - The code is organized in sections for better readability. This way it is more understandable when read by others. In the program, we have the implementation
    and game logic. Spells.txt contatins the game data.

  i. Headers
    - The headers included are libraries to be used throughout the program.
  
  ii. Function Declarations
    - Includes the headers of the functions that will be used in the program without their implementation. The implementations are provided after main.
      The purpose of this is solely an organization one, as well as informing the client what functions to expect in the program.

  iii. Main
    - Includes the implementation and the logic of the game.

  iv. Functions Implementations
    - Includes the functions stated in the function declarations sections with their implementations.
  
8. Code Documentation
    - The codebase includes comments that detail functionality at both the micro and macro levels, and clarify any code snippets that may be ambiguous. Above 
      each function, there is the purpose of the code. In separate branch, we included specifications for the program.

9. Challenges faced
    - During the devolopment of the program, managing dynamic memory allocations and mastering the syntax of C posed challenges. The program required careful
      and attentive memory management to prevent memory leaks and segmentation faults. Additionally, the syntax of C, though not very different from Java, 
      demanded more precision and attention as it focuses on miniscule details one need not worry about in Java, such as pointers, strings and garbage 
      collection.
  
10. Testing:
    - Unit testing was written for each function to validate their correctness in isolation. Then, integration tests were performed to
      ensure that the entire  code functions properly. The test cases may be found in the branch "Testing"

10. Performance: 
    - Spell Master is a game that runs smoothly and successfully. The methods ensure flexibility in managing dynamic memory allocation and deallocation. For 
      quick and easy access, linked lists are used to arrange spells alphabetically by their initial letters. Because of the sound logic of the game, which 
      includes validation of the players' moves and determining the prerequisites for a successful move, playing is made fluid and responsive. The client and 
      the bot take turns, adding a degree of unpredictability that improves the overall gameplay. The coin toss determines who starts.

11. Future Work: 
    - By pursuing these paths, Spell Master can be improved:
        i. Enhancing the bot's intelligence 
              - Improve the bot's ability to make decisions by using more complex algorithms or machine learning. This can entail looking for trends in the 
                client's movements to add strategy to the bot's decision-making.

        ii. Scalability
              - Make the code more efficient to manage bigger data sets; this may involve adding data structures or methods that speed up search and retrieval. 

        iii. User Interface 
              - To improve the overall game experience, implement a graphical user interface (GUI). The game may be made more engaging and fun by adding 
                animations, spell icons, visual effects, and a visually appealing interface with a user-friendly layout.

        iv. Multiplayer Support
              - Make the game compatible with multiplayer features so that more than two people can play at once. One possible solution to this would be to 
                implement a turn-based system in which each participant takes turns independently from each other.

        v. Game data
              - Include a feature that keeps track of and shows game data, such as the bot's performance, average game time, and the number of victories for 
                each participant. Players can monitor their advancement and it introduces a competitive aspect.

        vi. Difficulty Levels:
              - Provide the bot with a variety of difficulty settings so that users can select from a range of challenging options, such as timed challenges, 
                or extreme levels, or easy levels with hp.

14. Conclusion
    - A fun and distinctive gaming experience may be had with the SpellMaster Duel game code. More elements like user interface, dynamic conversation, 
      scoring, and an interactive player spellbook might make this project more entertaining and imaginative with a magical execution.
