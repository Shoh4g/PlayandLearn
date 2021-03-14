# Play_And_Learn

# ENGG1340: Computer Programming II

______________________________________________________________________________________________________________________________________________________________________

## Team Members:-

* Group Number:  182

* Name: Sabyasachi Purkayastha
  UID: 3035729708

* Name: AHMED Masood
  UID: 3035812127
______________________________________________________________________________________________________________________________________________________________________

# Description of the text-based game:-

* The game which we are implementing is an education based text game. The subject is chemisty and the motive of the game is to act as a supplement to text books and revision guides.
* The game/project will consist of 3 levels. The three levels correspond to 3 topics of chemistry. Each level is further divided into 3 difficulty levels: easy, medium, hard. Player starts with a certain health. Each wrong answer results in reduction of his health by a certain amount. If his health decreases below a certain level he loses the game. 
* We will allow a user to heal .i.e. everytime his health is low, the user will be asked whether he wants to roll dice to increase his health. If his guess score matches the number on the dice score his health increases. For the first 2 times, nothing happens if he guesses wrong. later on, wrong guess will decrease his health.  * After every topic finishes, his score is displayed. If the game finishes, a report card will be generated. The report card holds the record of his performance in all topics. His report card will include a percentile and a letter grade.In the end, the user will also get feedback on each topic based on his grade.
* The questions will be answered by the user through two ways. One way is by selecting from the given options by typing in the letter that is representing the option. The other way will be typing in the answers without options.

______________________________________________________________________________________________________________________________________________________________________

# Compilation and execution instructions

To compile and run the code, enter:

```
make game
./Play_And_Learn

```
______________________________________________________________________________________________________________________________________________________________________


# Features which we will implement!

## How are random events implemented in this project?

* We will implement a mini-lucky roll the dice within the education game. So while generating random numbers for the dice, we will rand() function to generate the number. If the guess of the user matches with the generated number, the user will gain energy points. 
* Random Function to randomly select questions for the user. The questions, answers, and options will be stored in data structures. 

## How do we use data structures?

* We will use arrays use to store answers to questions, scores of the user, and health of the user!
* User status, name, health, scores will also be stored in the data structures.

## Use Of File input/output:
 * All of the user data will be stored in a file.
 * Some of the game variables would be also written in files to maintain proper records of game choices and other implementation of game features.
 * If one player quits the game in the middle of the game, he/she can restart from last saved checkpoint by entering name and loading data.
 * Final report will also be stored in a file as a history of the user's progress.

## How Do We Impliment Program code in multiple files?
 * Program code will be stored in multiple files to implement the game functionality without any errors.
 * These files would help to regulate the process used in the game.
 
## Non-Standard C/C++ Libraries:

* #include <time.h> : Used to initialize seed of srand to current time
* #include <unistd.h> : Used to impliment sleep and usleep functions in the game

_____________________________________________________________________________________________________________________________________________________________________

# In A Nutshell:

Our game begins by greeting the user followed by taking in user data.I.e. Name of the user. This data will be entered into a file using input and output streams. The purpose of doing this is to countercheck and provide user with his previous record if it exists and prompt the user to use that previous record if he had left the game incomplete before, or give the user advide on how to improve the score.The advantage of this feature is that no other player can access data for another user. 

The introduction gives a detailed explanation of the game and prompts the user to continue when they’re done reading it.

Once the game begins, the user is prompted to answer questions from topics that the user has selected. These questions are generated randomly from structures that store these questions.

The game includes a healing mechanisim *'The Lucky-Dice'*.

The game at somepart will incorporate different features like the typewriter effect and using sounds.

After each round the data is updated in the file. If the user quits the game in the middle of a round, they can restart from the last checkpoint.

In the end of the game, the report card of the user is shown with an advice and goodbye message is displayed. 

______________________________________________________________________________________________________________________________________________________________________
