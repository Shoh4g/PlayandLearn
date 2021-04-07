#include <iostream>
#include <string>
#include <cstdlib>  //for calling srand and rand functions
#include <ctime>    // for calling ctime

#include "barrier.h"
#include "functions.h"

using namespace std;

// A function declaration allowing the use of typewriter when needed
void typewriter( string str, int time );


//It returns true when a person wants to use healing chance
bool healer()
{
    char s;   // to get input from the user
    cout << endl;
    string line = "Do you want to heal or not (Y/N)\n";
    typewriter( line, 150000 );
    cin.get(s);

    // If y or Y is pressed, it tells that healing is needed
    if ( s == 'Y' || s == 'y' )
    {
        return true;
    }
    else
    {
        return false;
    }

}



//This function will return true or false according to the guess and will allow healing or not
// If guess matches with the number generated to be guessed, it returns true
bool random_guess()
{
    srand( time( NULL ) );   // initialising the seed
    int guess;
    int guessGenerator = ( rand() % 6 )+ 1;   // generating a random number
    cout << endl;
    string line = "Guess a number between 1 to 6\n";
    typewriter( line, 150000 );

    cin >> guess;

    cout << "Your guess is " << guess << endl << "The Number to be guessed is " << guessGenerator << endl;
    // Checking if guess is correct or not and the return accordingly
    if ( guess == guessGenerator )
    {
        return true;
    }
    else
    {
        return false;
    }
    
}